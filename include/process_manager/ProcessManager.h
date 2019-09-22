#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <vector>
#include <string>

class ProcessManager {
public:
    ProcessManager(short nProcesses, short nResources);
    virtual void addChildProcess(int parentPID, int childPID) = 0;

    virtual bool create(std::vector<std::string>& command) = 0;
    virtual bool destroy(std::vector<std::string>& command) = 0;
    virtual bool request(std::vector<std::string>& command) = 0;
    virtual bool release(std::vector<std::string>& command) = 0;
    virtual bool timeout() = 0;
    virtual bool init() = 0;

    bool runCommand(std::vector<std::string>& command);

    virtual ~ProcessManager();

protected:
    short maxProcesses;
    short maxResources;
    short numProcesses;

};

#endif