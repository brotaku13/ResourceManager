#ifndef PCB_H
#define PCB_H

#include <list>
#include <algorithm>

class PCB {
public:
    static const short ReadyState = 0;
    static const short BlockedState = 1;

    PCB();
    PCB(int state, int parent);
    void reset();
    bool hasChild(int pid);
    bool holdingResource(int rid);
    void releaseResource(int rid);
    void insertChild(int childPID);
    bool removeChild(int pid);
    void setState(short newState);
    void insertResource(int rid);
    std::list<int>& getChildren();
    std::list<int>& getResources();
    int getParent();

protected:
    unsigned int state : 1;
    int parent;
    std::list<int> children;
    std::list<int> resources;
};

#endif