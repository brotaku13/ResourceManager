#ifndef EXTENDED_SCHEDULER_H
#define EXTENDED_SCHEDULER_H

#include <scheduler/Scheduler.h>
#include <list>
#include <vector>
#include <algorithm>

class ExtendedScheduler : public Scheduler {
public:
    ExtendedScheduler();

    int getRunningProcess();
    void insert(int newProcessPID, int priority);
    void remove(int pid);
    void emptyReadyList();
    void contextSwitch();

    ~ExtendedScheduler();
private:
    int numPriorityLevels;
    std::vector<std::list<int>> readyList;
};

#endif