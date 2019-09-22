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

bool PCB::hasChild(int pid)
{
    return std::find(children.begin(), children.end(), pid) != children.end();
}

bool PCB::holdingResource(int rid)
{
    return std::find(resources.begin(), resources.end(), rid) != resources.end();
}

void PCB::releaseResource(int rid)
{
    auto it = std::find(resources.begin(), resources.end(), rid);
    if(it !=  resources.end())
    {
        resources.erase(it);
    }
}

void PCB::setState(short newState)
{
    if(newState != PCB::BlockedState and newState != PCB::ReadyState)
        throw std::exception();
    
    state = newState;
}

std::list<int>& PCB::getChildren() { return children; }

void PCB::insertResource(int rid)
{
    resources.push_back(rid);
}

int PCB::getParent() {return parent; }