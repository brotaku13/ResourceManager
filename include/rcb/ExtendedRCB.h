#ifndef EXTENDED_RCB_H
#define EXTENDED_RCB_h

#include <rcb/RCB.h>

class ExtendedRCB : public RCB {
public:
    ExtendedRCB(int numResources);
    void reset();
    ~ExtendedRCB();
private:
    const int maxAvailable;
    int numAvailable;
};

#endif