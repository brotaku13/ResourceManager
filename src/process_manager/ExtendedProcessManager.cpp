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

bool ExtendedProcessManager::create(std::vector<std::string>& command)
{
    return true;
}

bool ExtendedProcessManager::destroy(std::vector<std::string>& command)
{
    return true;
}

bool ExtendedProcessManager::request(std::vector<std::string>& command)
{
    return true;
}
bool ExtendedProcessManager::release(std::vector<std::string>& command)
{
    return true;
}

bool ExtendedProcessManager::timeout()
{
    return true;
}

void ExtendedProcessManager::freePCB(int pid)
{
    
}

void ExtendedProcessManager::addChildProcess(int parentPID, int childPID)
{

}


int ExtendedProcessManager::insertIntoProcessList(ExtendedPCB* newPCB)
{
    //find first index where the value is nullptr

    auto index = std::find(plist.begin(), plist.end(), nullptr);
    if(index == plist.end())
        throw std::exception(); //no more space? should never happen
    *index = newPCB;
    ++numProcesses;
    return std::distance(plist.begin(), index);
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


ExtendedProcessManager::~ExtendedProcessManager()
{
    emptyProcessList();
}