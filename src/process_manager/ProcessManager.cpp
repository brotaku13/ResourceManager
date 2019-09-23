#include <process_manager/ProcessManager.h>

ProcessManager::ProcessManager(short nProcesses, short nResources) 
    : maxProcesses(nProcesses), maxResources(nResources), numProcesses(0){}

bool ProcessManager::runCommand(std::vector<std::string>& command)
{
    std::string& commandType = command[0];
    if(commandType == "cr")
        return this->create(command);
    else if (commandType == "de")
        return this->destroy(command);
    else if (commandType == "rq")
        return this->request(command);
    else if (commandType == "rl")
        return this->release(command);
    else if (commandType == "to")
        return this->timeout();
    else if (commandType == "in")
        return this->init();
    else
        return false;
}

bool ProcessManager::validPID(int pid)
{
    return pid >= 0 && pid < maxProcesses;
}

bool ProcessManager::validRID(int rid)
{
    return rid >= 0 && rid < maxResources;
}

ProcessManager::~ProcessManager(){}