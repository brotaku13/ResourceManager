#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>

class Scheduler {
public:
    Scheduler();
    virtual void insert(int newProcessPID) = 0;
    virtual int getRunningProcess() = 0;
    virtual void emptyReadyList() = 0;
    virtual void contextSwitch() = 0;
    void printRunningProcess();
    virtual ~Scheduler();

protected:
};

#endif