#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
public:
    Scheduler();
    virtual void insert(int newProcessPID) = 0;
    virtual int getRunningProcess() = 0;
    virtual void emptyReadyList() = 0;
    virtual ~Scheduler();

protected:
};

#endif