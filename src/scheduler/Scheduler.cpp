#include <scheduler/Scheduler.h>

Scheduler::Scheduler(){}

void Scheduler::printRunningProcess()
{
    int pid = this->getRunningProcess();
    std::cout << pid << ' ';
}
Scheduler::~Scheduler(){}