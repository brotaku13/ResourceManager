#include <process_manager/BasicProcessManager.h>

BasicProcessManager::BasicProcessManager(short nProcesses, short nResources) 
    : ProcessManager(nProcesses, nResources), 
      plist(nProcesses, nullptr), rlist(nResources, BasicRCB())
{
    init();
}


void BasicProcessManager::insertIntoReadyList(int newProcessPID)
{
    scheduler.insert(newProcessPID);
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
    ++ProcessManager::numProcesses;
    return std::distance(plist.begin(), index);
}

bool BasicProcessManager::create(std::vector<std::string>& command)
{
    // check to make sure we aren't going over the amount
    if(ProcessManager::numProcesses >= ProcessManager::maxProcesses)
        return false;
    
    int parentProc = scheduler.getRunningProcess();

    //create the new process
    PCB* newProc = new PCB(PCB::ReadyState, parentProc);

    //insert the process into the list
    int newPid = insertIntoProcessList(newProc);
    //track child
    plist[parentProc]->insertChild(newPid);
    
    std::cout << "process " << newPid << " created" << '\n';
    return true;
}

bool BasicProcessManager::destroy(std::vector<std::string>& command)
{
    std::cout << "Received command " << command[0] << " " << command[1] << '\n';
    return true;
}
bool BasicProcessManager::request(std::vector<std::string>& command)
{
        std::cout << "Received command " << command[0] << " " << command[1] << '\n';
    return true;
}
bool BasicProcessManager::release(std::vector<std::string>& command)
{
    std::cout << "Received command " << command[0] << " " << command[1] << '\n';
    return true;
}
bool BasicProcessManager::timeout()
{
    std::cout << "Received command to"  << '\n';
    return true;
}
bool BasicProcessManager::init()
{
    std::cout << "Received command in"  << '\n';
    //resets system to default state
    // remove all PCB blocks in plist
    emptyProcessList();
    ProcessManager::numProcesses = 0;

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
        std::cerr << "could not insert into process list" << '\n';
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
        // iter->reset(); //if we use static pcbs
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

void BasicProcessManager::addChildProcess(int parentPID, int childPID)
{
    std::cout << parentPID << childPID;
}

BasicProcessManager::~BasicProcessManager()
{
    emptyProcessList();
}