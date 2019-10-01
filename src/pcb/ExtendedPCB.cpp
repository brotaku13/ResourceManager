#include <pcb/ExtendedPCB.h>

ExtendedPCB::ExtendedPCB(int priority) : priority(priority){}

ExtendedPCB::ExtendedPCB(int priority, int parentPID) : 
    PCB(PCB::ReadyState, parentPID), 
    priority(priority){}

std::list<resourceNode>::iterator ExtendedPCB::findResource(int rid)
{
    return std::find_if(resources.begin(), resources.end(), 
                        [&](resourceNode const& rn){ return rn.rid == rid;});
}

int ExtendedPCB::getPriority() { return priority; }

int ExtendedPCB::numUnitsHeld(int rid)
{
    auto it = findResource(rid);
    if(it == resources.end())
        return 0;
    else
        return it->held;
}

bool ExtendedPCB::holdingResource(int rid)
{
    return findResource(rid) != resources.end();
}

void ExtendedPCB::insertResource(int rid, int units)
{
    auto it = findResource(rid);
    if(it == resources.end())
    {
        resourceNode n(rid, units);
        resources.push_back(n);
    }
    else
    {
        it->held += units;
    }
}

//returns number of units released
void ExtendedPCB::releaseResource(int rid, int units)
{
    auto it = findResource(rid);
    if(units >= 0 && it != resources.end())
    {
        if(units > it->held)
            throw std::exception();

        if(it->held == units)
            resources.erase(it);
        else
            it->held -= units;   
    }
    else
        throw std::exception();
}

ExtendedPCB::~ExtendedPCB(){}