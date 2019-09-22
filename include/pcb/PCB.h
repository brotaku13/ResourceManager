#ifndef PCB_H
#define PCB_H

#include <list>

class PCB {
public:
    static const short ReadyState = 0;
    static const short BlockedState = 1;

    PCB();
    PCB(int state, int parent);
    void reset();
    void insertChild(int childPID);

protected:
    unsigned int state : 1;
    int parent;
    std::list<int> children;
    std::list<int> resources;
};

#endif