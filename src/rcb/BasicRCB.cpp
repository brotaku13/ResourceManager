#include <rcb/BasicRCB.h>

BasicRCB::BasicRCB() : state(1){}

void BasicRCB::reset()
{
    waitingList.clear();
    state = BasicRCB::free;
}

int BasicRCB::waitingListSize()
{
    return static_cast<int>(waitingList.size());
}

void BasicRCB::setState(short newState)
{
    if (newState != BasicRCB::allocated && newState != BasicRCB::free)
        throw std::exception();
    state = newState;
}

unsigned int BasicRCB::getState()
{
    return state;
}

int BasicRCB::getNextProcess()
{
    if(waitingList.size() > 0)
        return waitingList.front();
    else
        throw std::exception();
}

void BasicRCB::insertProcess(int pid)
{
    waitingList.push_back(pid);
}

BasicRCB::~BasicRCB(){}