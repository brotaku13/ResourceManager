#include <process_manager/BasicProcessManager.h>

BasicProcessManager::BasicProcessManager(short nProcesses, short nResources) 
    : ProcessManager(nProcesses, nResources), 
      plist(nProcesses, nullptr), rlist(nResources, BasicRCB())
{
    init();
}

//inserts a new PCB into the plist vector. 
// returns the index it was inserted
int BasicProcessManager::insertIntoProcessList(PCB* newPCB)
{
    //find first index where the value is nullptr

    auto index = std::find(plist.begin(), plist.end(), nullptr);
    if(index == plist.end())
        throw std::exception(); //no more space? should never happen
    *index = newPCB;
    ++numProcesses;
    return std::distance(plist.begin(), index);
}

bool BasicProcessManager::create(std::vector<std::string>& command)
{
    // check to make sure we aren't going over the amount
    if(numProcesses >= maxProcesses)
        return false;
    
    int parentProc = scheduler.getRunningProcess();
    command[0]; //to keep compiler from complaining about unused variables
    //create the new process
    PCB* newProc = new PCB(PCB::ReadyState, parentProc);

    //insert the process into the process list
    int newPid = insertIntoProcessList(newProc);
    //update children of calling project
    plist[parentProc]->insertChild(newPid);
    
    //place this process on ready list
    scheduler.insert(newPid);

    std::cout << "process " << newPid << " created" << '\n';
    return true;
}

bool BasicProcessManager::destroy(std::vector<std::string>& command)
{
    int pid = std::stoi(command[1]);
    if(!validPID(pid) || !currentRunningProcess().hasChild(pid))
        return false; //process does not exist in children list
    
    int nDestoyed = destroyHelper(pid);

    std::cout << nDestoyed << " processes destroyed" << '\n';
    return true;
}

//recursive function that returns the total number of children processes destroyed
int BasicProcessManager::destroyHelper(int pid)
{
    int nDeleted = 0;
    PCB& proc = getProcess(pid);
    std::list<int>& children = proc.getChildren();
    while (children.size() != 0)
    {
        int n = children.front();
        children.pop_front();
        nDeleted += destroyHelper(n);
    }

    //remove child process from list of children in parent
    getProcess(proc.getParent()).removeChild(pid);

    //remove proc from ready list
    scheduler.remove(pid);

    //release all resources that proc is holding
    releaseAll(proc);

    freePCB(pid);
    --numProcesses;

    return nDeleted + 1;
}



bool BasicProcessManager::request(std::vector<std::string>& command)
{
    int rid = std::stoi(command[1]);

    int pid = scheduler.getRunningProcess();
    PCB& proc = getProcess(pid);
    
    //if the resource doesn't exist or we are already holding the resource
    if(!validRID(rid) || pid == 0 || proc.holdingResource(rid))
        return false;

    BasicRCB& rcb = rlist[rid];
    if(rcb.getState() == BasicRCB::free)
    {
        //set status to allocated
        rcb.setState(BasicRCB::allocated);
        //add the resource to the resources the current process is holding
        proc.insertResource(rid);
        std::cout << "resource " << rid << " allocated" << '\n';
    }
    else
    {
        //set process to blocked
        proc.setState(PCB::BlockedState);
        //remove from ready list
        scheduler.remove(pid);
        //insert into back of waiting list
        rcb.insertProcess(pid);
        std::cout << "process " << pid << " blocked" << '\n';
        scheduler.printRunningProcess();
    }
    
    return true;
}
bool BasicProcessManager::release(std::vector<std::string>& command)
{
    //basic error checking
    int rid = std::stoi(command[1]);
    PCB& proc = currentRunningProcess();
    if(!validRID(rid) || !proc.holdingResource(rid))
        return false;

    if(release(proc, rid))
    {
        std::cout << "resource " << rid << " released" << '\n';
        return true;
    }
    else
        return false;
    
}
bool BasicProcessManager::release(PCB& process, int rid)
{
    //release resource by removing from resource list
    process.releaseResource(rid);
    BasicRCB& rsc = rlist[rid];
    if(rsc.waitingListSize() == 0)
    {
        rsc.setState(BasicRCB::free);
    }
    else
    {
        //take process from head of waiting list and move it to the ready list
        int pid = rsc.getNextProcess();
        scheduler.insert(pid);
        
        // set state of process to ready
        PCB& proc = getProcess(pid);
        proc.setState(PCB::ReadyState);
        //insert r into resources of that process
        proc.insertResource(rid);
    }
    
    return true;
}

bool BasicProcessManager::releaseAll(PCB& process)
{
    std::list<int> resources = process.getResources(); //calls copy constructor
    for(int i: resources)
    {
        release(process, i);
    }
    return true;
}

bool BasicProcessManager::timeout()
{
    scheduler.contextSwitch();
    scheduler.printRunningProcess();
    return true;
}
bool BasicProcessManager::init()
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
    PCB *initProc = new PCB(); //new process has parent of -1 and empty lists
    
    try{
        int pid = insertIntoProcessList(initProc);
        scheduler.insert(pid);
    } catch (std::exception){
        return false;
    }

    return true;
}

void BasicProcessManager::emptyProcessList()
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

void BasicProcessManager::deallocateResourceList()
{
    for(BasicRCB& r: rlist)
    {
        r.reset();
    }
}

PCB& BasicProcessManager::currentRunningProcess()
{
    return getProcess(scheduler.getRunningProcess());
}

PCB& BasicProcessManager::getProcess(int index)
{
    return *(plist[index]);
}

void BasicProcessManager::freePCB(int pid)
{
    if(validPID(pid))
    {
        delete plist[pid];
        plist[pid] = nullptr;
    }
}

BasicProcessManager::~BasicProcessManager()
{
    emptyProcessList();
}