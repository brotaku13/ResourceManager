#ifndef EXTENDED_PCB_H
#define EXTENDED_PCB_H

#include <pcb/PCB.h>

class ExtendedPCB : public PCB {
public:
    ExtendedPCB(int priority);
    ExtendedPCB(int priority, int parentPID);

    ~ExtendedPCB();
private:
    int priority : 2;
};

#endif