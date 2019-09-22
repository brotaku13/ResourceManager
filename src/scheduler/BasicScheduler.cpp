#include <scheduler/BasicScheduler.h>

BasicScheduler::BasicScheduler(){}

int BasicScheduler::getRunningProcess()
{
    if(readyList.size() > 0)
        return readyList.front();
    else
        return -1;
}

void BasicScheduler::insert(int newProcessPID)
{
    readyList.push_back(newProcessPID);
}

void BasicScheduler::emptyReadyList()
{
    readyList.clear();
}

BasicScheduler::~BasicScheduler(){}