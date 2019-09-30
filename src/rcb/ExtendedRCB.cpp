#include <rcb/ExtendedRCB.h>

ExtendedRCB::ExtendedRCB(int numResources) : 
    maxAvailable(numResources), numAvailable(numResources){}

ExtendedRCB::~ExtendedRCB(){}

void ExtendedRCB::reset()
{
    numAvailable = maxAvailable;
}