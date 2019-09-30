#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <vector>
#include <string>

class ProcessManager {
public:
    ProcessManager(short nProcesses, short nResources);
    virtual bool create(std::vector<std::string>& command) = 0;
    virtual bool destroy(std::vector<std::string>& command) = 0;
    virtual bool request(std::vector<std::string>& command) = 0;
    virtual bool release(std::vector<std::string>& command) = 0;
    virtual bool timeout() = 0;
    virtual bool init() = 0;
    virtual void freePCB(int pid) = 0;

    bool runCommand(std::vector<std::string>& command);
    bool validPID(int pid);
    bool validRID(int rid);

    virtual ~ProcessManager();

protected:
    
    short maxProcesses;
    short maxResources;
    short numProcesses;

};

#endif