
#ifndef EXTENDED_RCB_H
#define EXTENDED_RCB_h

#include <rcb/RCB.h>
#include <algorithm>

struct waitlistNode {
    int pid;
    int unitsRequested;
    waitlistNode(int pid, int requested): pid(pid), unitsRequested(requested){};
};

class ExtendedRCB : public RCB {
public:
    ExtendedRCB(int numResources);
    void reset();
    int getMaxInventory();
    int getInventory();
    void reduceInventory(int units);
    void increaseInventory(int units);
    void insertProcess(int pid, int units);
    void removeProcess(int pid);
    int waitingListSize();
    void pop();
    waitlistNode front();
    ~ExtendedRCB();
private:
    const int maxInventory;
    int inventory; //state
    std::list<waitlistNode> waitingList;
};

#endif