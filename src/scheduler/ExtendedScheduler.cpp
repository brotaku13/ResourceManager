#include <scheduler/ExtendedScheduler.h>

ExtendedScheduler::ExtendedScheduler() : numPriorityLevels(3),  readyList(3, std::list<int>()){}

ExtendedScheduler::~ExtendedScheduler(){}

int ExtendedScheduler::getRunningProcess()
{
    for(int i = numPriorityLevels - 1;  i >= 0; ++i)
    {
        std::list<int>& rl = readyList[i];
        if(!rl.empty())
        {
            return rl.front();
        }
    }
    //if we get here something went terribly wrong
    throw std::exception();
}

void ExtendedScheduler::contextSwitch()
{
    //equivalent to Timeout()
    std::list<int>* rl = nullptr;
    for(int i = numPriorityLevels - 1; i >= 0; ++i)
    {
        if(!readyList[i].empty())
        {
            rl = &(readyList[i]);
            break;
        }
    }
    if (!rl)
    {
        //could not find a non-empty list
        throw std::exception();
    }

    if(rl->size() > 1)
    {
        int pid = rl->front();
        rl->pop_front();
        rl->push_back(pid);
    }
}

void ExtendedScheduler::insert(int newProcessPID, int priority)
{
    if(priority < 0 || priority > 2)
    {
        throw std::exception();
    }
    else
    {
        readyList[priority].push_back(newProcessPID);
    }
}

void ExtendedScheduler::remove(int pid)
{
    if(pid == 0)
        throw std::exception();

    for(std::list<int>& rl: readyList)
    {
        auto it = std::find(rl.begin(), rl.end(), pid);
        if(it != rl.end())
        {
            rl.erase(it);
            break;
        }
    }
}

void ExtendedScheduler::emptyReadyList()
{
    for(std::list<int>& rl: readyList)
    {
        rl.clear();
    }
}