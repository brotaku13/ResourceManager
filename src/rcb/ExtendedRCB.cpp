#include <rcb/ExtendedRCB.h>

ExtendedRCB::ExtendedRCB(int numResources) : 
    maxInventory(numResources), inventory(numResources){}

ExtendedRCB::~ExtendedRCB(){}

int ExtendedRCB::getMaxInventory() { return maxInventory; }
int ExtendedRCB::getInventory() { return inventory; }
int ExtendedRCB::waitingListSize() { return waitingList.size(); }

void ExtendedRCB::reduceInventory(int units)
{
    if(units >= 0 && units <= inventory)
        inventory -= units;
    else
        throw std::exception();
    
}

void ExtendedRCB::increaseInventory(int units)
{
    if(units >= 0 && inventory + units <= maxInventory)
        inventory += units;
    else
        throw std::exception();
    
}

void ExtendedRCB::removeProcess(int pid)
{
    waitingList.remove_if([&](waitlistNode const& wln){ return wln.pid == pid;});
}

void ExtendedRCB::insertProcess(int pid, int units)
{
    if(pid < 1 || units < 0 || units > maxInventory)
        throw std::exception();

    //check to see if they are already waiting 
    auto it = find_if(waitingList.begin(), waitingList.end(), 
        [&](waitlistNode const& wln){ return wln.pid == pid; });

    if(it == waitingList.end())
    {
        waitlistNode wln(pid, units);
        waitingList.push_back(wln);
    }
    else
    {
        if(it->unitsRequested + units > maxInventory)
            throw std::exception();
        it->unitsRequested += units;
    }
}

waitlistNode ExtendedRCB::front()
{
    if(!waitingList.empty())
    {
        return waitingList.front();
    }
    else
        throw std::exception();
}   

void ExtendedRCB::pop()
{
    if(!waitingList.empty())
        waitingList.pop_front();
    else
        throw std::exception();
}

void ExtendedRCB::reset()
{
    waitingList.clear();
    inventory = maxInventory;
}