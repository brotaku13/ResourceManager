#ifndef BASIC_SCHEDULER_H
#define BASIC_SCHEDULER_H
#include <scheduler/Scheduler.h>
#include <list>
#include <algorithm>

class BasicScheduler : public Scheduler {
public:
    BasicScheduler();
    int getRunningProcess();
    void emptyReadyList();
    void insert(int newProcessPID);
    void remove(int pid);
    void contextSwitch();
    ~BasicScheduler();
private:
    std::list<int> readyList;
};

#endif