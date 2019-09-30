#include <pcb/ExtendedPCB.h>

ExtendedPCB::ExtendedPCB(int priority) : priority(priority){}

ExtendedPCB::ExtendedPCB(int priority, int parentPID) : 
    PCB(PCB::ReadyState, parentPID), 
    priority(priority){}



ExtendedPCB::~ExtendedPCB(){}

