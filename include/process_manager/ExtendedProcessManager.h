#ifndef EXTENDED_PROCESS_MANAGER_H
#define EXTENDED_PROCESS_MANAGER_H

#include <process_manager/ProcessManager.h>
#include <pcb/ExtendedPCB.h>
#include <rcb/ExtendedRCB.h>
#include <scheduler/ExtendedScheduler.h>

#include <vector>
#include <algorithm>
#include <iostream>

class ExtendedProcessManager : public ProcessManager {
public:
    ExtendedProcessManager(short nProcesses, short nResources);
    void emptyProcessList();
    void deallocateResourceList();
    int insertIntoProcessList(ExtendedPCB* newPCB);

    ExtendedPCB& currentRunningProcess();
    ExtendedPCB& getProcess(int index);
    ExtendedRCB& getResource(int rid);

    bool create(std::vector<std::string>& command);
    bool destroy(std::vector<std::string>& command);

    bool request(std::vector<std::string>& command);
    bool release(std::vector<std::string>& command);
    bool timeout();
    bool init();

    ~ExtendedProcessManager();
private:
    std::vector<ExtendedPCB*> plist;
    std::vector<ExtendedRCB> rlist;
    ExtendedScheduler scheduler;

    void clearWaitingLists(int pid);
    int destroyHelper(int pid);
    void release(ExtendedPCB& proc, int rid, int units);
    bool releaseAll(ExtendedPCB& process);
    void freePCB(int pid);
    void initRlist();
};

#endif