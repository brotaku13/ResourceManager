#include <process_manager/ExtendedProcessManager.h>

ExtendedProcessManager::ExtendedProcessManager(short nProcesses, short nResources) 
        : ProcessManager(nProcesses, nResources),
            plist(nProcesses, nullptr)
{
    initRlist();
    init();
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
    if(priority != 1 || priority != 2)
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


    scheduler.printRunningProcess();
    return true;
}

bool ExtendedProcessManager::request(std::vector<std::string>& command)
{
    return true;
}
bool ExtendedProcessManager::release(std::vector<std::string>& command)
{


    scheduler.printRunningProcess();
    return true;
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

void ExtendedProcessManager::addChildProcess(int parentPID, int childPID)
{

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

ExtendedProcessManager::~ExtendedProcessManager()
{
    emptyProcessList();
}