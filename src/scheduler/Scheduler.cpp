#include <scheduler/Scheduler.h>

Scheduler::Scheduler(){}

void Scheduler::printRunningProcess()
{
    int pid = this->getRunningProcess();
    std::cout << "process " << pid << " running" << '\n';
}
Scheduler::~Scheduler(){}