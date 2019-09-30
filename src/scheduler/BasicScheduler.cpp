#include <scheduler/BasicScheduler.h>

BasicScheduler::BasicScheduler(){}

int BasicScheduler::getRunningProcess()
{
    if(!readyList.empty())
        return readyList.front();
    else
        throw std::exception();
}

void BasicScheduler::insert(int newProcessPID)
{
    readyList.push_back(newProcessPID);
}

void BasicScheduler::remove(int pid)
{
    auto it = std::find(readyList.begin(), readyList.end(), pid);
    if(it != readyList.end())
        readyList.erase(it);
}

void BasicScheduler::emptyReadyList()
{
    readyList.clear();
}

void BasicScheduler::contextSwitch()
{
    if(readyList.size() > 1)
    {
        int pid = readyList.front();
        readyList.pop_front();
        readyList.push_back(pid);
    }
}

BasicScheduler::~BasicScheduler(){}