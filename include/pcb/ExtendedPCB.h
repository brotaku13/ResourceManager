#ifndef EXTENDED_PCB_H
#define EXTENDED_PCB_H

#include <pcb/PCB.h>

struct resourceNode {
    int rid;
    int held;

    resourceNode(int rid, int requested): rid(rid), held(requested){};
};

class ExtendedPCB : public PCB {
public:
    ExtendedPCB(int priority);
    ExtendedPCB(int priority, int parentPID);

    int numUnitsHeld(int rid);
    bool holdingResource(int rid);
    void releaseResource(int rid, int units);
    void insertResource(int rid, int units);
    std::list<resourceNode>& getResources() { return resources; }
    int getPriority();

    ~ExtendedPCB();
private:
    std::list<resourceNode>::iterator findResource(int rid);

    unsigned int priority : 2;
    std::list<resourceNode> resources;
};

#endif