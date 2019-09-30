#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <processor/Processor.h>
#include <shell/BasicShell.h>
#include <shell/ExtendedShell.h>
#include <process_manager/BasicProcessManager.h>
#include <process_manager/ExtendedProcessManager.h>

#include <memory>
#include <vector>
#include <iostream>

class Processor {

public:
    static const short BASIC = 0;
    static const short EXTENDED = 1;
    const short nProcesses = 16;
    const short nResources = 4;
    
    Processor(int managerType);
    void run();
    ~Processor();

private:
    std::unique_ptr<Shell> shell;
    std::unique_ptr<ProcessManager> processManager;
};

#endif