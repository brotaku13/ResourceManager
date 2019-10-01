#include <process_manager/ExtendedProcessManager.h>

ExtendedProcessManager::ExtendedProcessManager(short nProcesses, short nResources) 
        : ProcessManager(nProcesses, nResources),
            plist(nProcesses, nullptr)
{
    initRlist();
}

void ExtendedProcessManager::initRlist()
{
    rlist.clear();
    rlist.push_back(ExtendedRCB(1));
    rlist.push_back(ExtendedRCB(1));
    rlist.push_back(ExtendedRCB(2));
    rlist.push_back(ExtendedRCB(3));
}

bool ExtendedProcessManager::init()
{
    //resets system to default state
    // remove all PCB blocks in plist
    emptyProcessList();
    numProcesses = 0;

    //remove all items in ready descriptorlist
    scheduler.emptyReadyList();

    //set all resources to be free
    deallocateResourceList();
    
    //insert process 0 to beginning of ready list and plist[0]
    ExtendedPCB *initProc = new ExtendedPCB(0); //new process has parent of -1 and empty lists
    
    try{
        int pid = insertIntoProcessList(initProc);
        scheduler.insert(pid, 0);
    } catch (std::exception){
        return false;
    }

    scheduler.printRunningProcess();
    return true;
}

int ExtendedProcessManager::insertIntoProcessList(ExtendedPCB* newPCB)
{
    auto index = std::find(plist.begin(), plist.end(), nullptr);
    if(index == plist.end())
        throw std::exception();
    
    *index = newPCB;
    ++numProcesses;
    return std::distance(plist.begin(), index);
}

bool ExtendedProcessManager::create(std::vector<std::string>& command)
{
    if(numProcesses >= maxProcesses)
        return false;

    int priority = std::stoi(command[1]);
    if(priority < 1 || priority > 2)
        return false;
    
    int parentProc = scheduler.getRunningProcess();
    ExtendedPCB* newProc = new ExtendedPCB(priority, parentProc);

    //insert into process list
    int newPid = insertIntoProcessList(newProc);

    // update children of running process
    plist[parentProc]->insertChild(newPid);

    //place this process on ready list
    scheduler.insert(newPid, priority);

    //call scheduler()
    scheduler.printRunningProcess();

    return true;
}

bool ExtendedProcessManager::destroy(std::vector<std::string>& command)
{
    int pid = std::stoi(command[1]);
    if(!validPID(pid) || !currentRunningProcess().hasChild(pid))
        return false;

    destroyHelper(pid);

    scheduler.printRunningProcess();
    return true;
}

int ExtendedProcessManager::destroyHelper(int pid)
{
    int nDeleted = 0;
    ExtendedPCB& proc = getProcess(pid);
    std::list<int>& children = proc.getChildren();
    while(children.size() != 0)
    {
        int n = children.front();
        children.pop_front();
        nDeleted += destroyHelper(n);
    }

    //remove child process from list of children in parent
    getProcess(proc.getParent()).removeChild(pid);

    //remove proc from readyList
    scheduler.remove(pid);

    //If process is currently waiting for a resource, remove from waiting list
    clearWaitingLists(pid);

    //release all resources that proc is holding
    releaseAll(proc);

    freePCB(pid);

    --numProcesses;

    return nDeleted + 1;
}

bool ExtendedProcessManager::releaseAll(ExtendedPCB& proc)
{
    std::list<resourceNode> resources = proc.getResources(); //calls copy constructor
    for(resourceNode& i: resources)
    {
        release(proc, i.rid, i.held);
    }
    return true;
}

/**
 * Clears a process from any waiting lists it may inhabit
*/
void ExtendedProcessManager::clearWaitingLists(int pid)
{
    //this is gonna be n^2 but whatever
    for(ExtendedRCB& rcb : rlist)
    {
        rcb.removeProcess(pid);
    }
}

//rq r k
// r = resource id (rid)
// k = number of that resource requested
bool ExtendedProcessManager::request(std::vector<std::string>& command)
{
    int rid = std::stoi(command[1]);
    int requestedUnits = std::stoi(command[2]);

    int pid = scheduler.getRunningProcess();
    ExtendedPCB& proc = getProcess(pid);

    //make sure input is valid and the incoming request is not from init
    if(!validRID(rid) || pid == 0)
        return false;

    ExtendedRCB& resource = getResource(rid);

    int numUnitsHeld = proc.numUnitsHeld(rid);
    int maxUnits = resource.getMaxInventory();
    //check to make sure we aren't over requesting for a given resource
    if(requestedUnits < 0 || numUnitsHeld + requestedUnits > maxUnits)
        return false;
    
    // now we do the actual code
    if(resource.getInventory() >= requestedUnits)
    {
        //then we can satisfy the request
        resource.reduceInventory(requestedUnits);
        proc.insertResource(rid, requestedUnits);
    }
    else
    {
        //we remove the process from the running list, 
        // set it as blocked, and add it to the resource waitlist

        proc.setState(PCB::BlockedState);

        //remove from readylist
        scheduler.remove(pid);
        
        //insert in waiting list
        resource.insertProcess(pid, requestedUnits);
    }
    //call scheduler()
    scheduler.printRunningProcess();
    return true;
}


bool ExtendedProcessManager::release(std::vector<std::string>& command)
{
    int rid = std::stoi(command[1]);
    int requestedUnits = std::stoi(command[2]);

    int pid = scheduler.getRunningProcess();
    ExtendedPCB& proc = getProcess(pid);

    //make sure input is valid and the incoming request is not from init
    //and that we are holding the resource
    if(!validRID(rid) || pid == 0 || !proc.holdingResource(rid) || requestedUnits < 0 || requestedUnits > proc.numUnitsHeld(rid))
        return false;

    release(proc, rid, requestedUnits);

    //run scheduler()
    scheduler.printRunningProcess();
    return true;
}

void ExtendedProcessManager::release(ExtendedPCB& proc, int rid, int units)
{
    ExtendedRCB& resource = getResource(rid);

    //remove resources from currently held units on process, 
    //removing from resources list if necessary
    proc.releaseResource(rid, units);

    //increase the state of the resource that was released
    resource.increaseInventory(units);

    //go through and try to service as many waiting processes as possible
    while(resource.waitingListSize() != 0 && resource.getInventory() > 0)
    {
        //grab the next process in line
        waitlistNode wln = resource.front();
        int newPid = wln.pid;

        // if we have enough units available, service it
        if(resource.getInventory() >= wln.unitsRequested)
        {
            //reduce the units available
            resource.reduceInventory(wln.unitsRequested);
            ExtendedPCB& newProcess = getProcess(newPid);
            //insert the resource into the list of held resources
            newProcess.insertResource(rid, wln.unitsRequested);
            //set the state to ready
            newProcess.setState(PCB::ReadyState);
            resource.pop();
            //place on readylist
            scheduler.insert(newPid, newProcess.getPriority());
        }
        else
            break;
    }
}

bool ExtendedProcessManager::timeout()
{
    scheduler.contextSwitch();
    scheduler.printRunningProcess();
    return true;
}

void ExtendedProcessManager::freePCB(int pid)
{
    if(validPID(pid))
    {
        delete plist[pid];
        plist[pid] = nullptr;
    }
}

void ExtendedProcessManager::deallocateResourceList()
{
    for(ExtendedRCB& r: rlist)
    {
        r.reset();
    }
}

void ExtendedProcessManager::emptyProcessList()
{
    auto iter = plist.begin();
    auto end = plist.end();
    while (iter != end)
    {
        if(*iter != nullptr)
        {
            delete *iter;
            *iter = nullptr;
        }
        ++iter;
    }
}


ExtendedPCB& ExtendedProcessManager::currentRunningProcess()
{
    return getProcess(scheduler.getRunningProcess());
}

ExtendedPCB& ExtendedProcessManager::getProcess(int index)
{
    return *(plist[index]);
}

ExtendedRCB& ExtendedProcessManager::getResource(int rid)
{
    return rlist[rid];
}

ExtendedProcessManager::~ExtendedProcessManager()
{
    emptyProcessList();
}