#include <pcb/PCB.h>

PCB::PCB(): state(PCB::ReadyState), parent(-1){}

PCB::PCB(int state, int parent): state(state), parent(parent){}

void PCB::reset()
{
    state = PCB::ReadyState;
    parent = -1;
    children.clear();
    resources.clear();
}

void PCB::insertChild(int childPID)
{
    children.push_back(childPID);
}