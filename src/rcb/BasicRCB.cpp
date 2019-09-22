#include <rcb/BasicRCB.h>

BasicRCB::BasicRCB() : state(1){}

void BasicRCB::reset()
{
    waitingList.clear();
    state = BasicRCB::free;
}

BasicRCB::~BasicRCB(){}