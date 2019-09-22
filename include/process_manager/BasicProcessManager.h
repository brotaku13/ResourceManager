#ifndef BASIC_PROCESS_MANAGER_H
#define BASIC_PROCESS_MANAGER_H

#include <process_manager/ProcessManager.h>
#include <pcb/PCB.h>
#include <rcb/BasicRCB.h>
#include <scheduler/BasicScheduler.h>

#include <vector>
#include <algorithm>
#include <iostream>

class BasicProcessManager : public ProcessManager {
public:
    BasicProcessManager(short nProcesses, short nResources);
    void addChildProcess(int parentPID, int childPID);
    void emptyProcessList();
    void deallocateResourceList();
    int insertIntoProcessList(PCB* newPCB);
    PCB& currentRunningProcess();
    PCB& getProcess(int index);

    bool create(std::vector<std::string>& command);
    bool destroy(std::vector<std::string>& command);
    int destroyHelper(int pid);
    bool request(std::vector<std::string>& command);
    bool release(std::vector<std::string>& command);
    bool release(PCB& process, int rid);
    bool timeout();
    bool init();

    ~BasicProcessManager();
private:
    std::vector<PCB*> plist;
    std::vector<BasicRCB> rlist;
    BasicScheduler scheduler;
};

#endif