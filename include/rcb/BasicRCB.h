#ifndef BASIC_RCB_H
#define BASIC_RCB_h

#include <rcb/RCB.h>

class BasicRCB : public RCB {
public:
    static const short free = 1;
    static const short allocated = 0;

    BasicRCB();
    void reset();
    ~BasicRCB();

private:
    unsigned int state : 1;
    std::list<int> waitingList;
};

#endif