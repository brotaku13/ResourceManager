#ifndef BASIC_SCHEDULER_H
#define BASIC_SCHEDULER_H
#include <scheduler/Scheduler.h>
#include <list>

class BasicScheduler : public Scheduler {
public:
    BasicScheduler();
    int getRunningProcess();
    void emptyReadyList();
    void insert(int newProcessPID);
    ~BasicScheduler();
private:
    std::list<int> readyList;
};

#endif