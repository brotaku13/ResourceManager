#include <processor/Processor.h>


Processor::Processor(int managerType)
{
    if(managerType == Processor::BASIC)
    {
        shell = std::unique_ptr<BasicShell>(new BasicShell);
        processManager = std::unique_ptr<BasicProcessManager>(new BasicProcessManager(nProcesses, nResources));
    }
    else if (managerType == Processor::EXTENDED)
    {
        shell = std::unique_ptr<ExtendedShell>(new ExtendedShell);
        processManager = std::unique_ptr<ExtendedProcessManager>(new ExtendedProcessManager(nProcesses, nResources));
    }
}

void Processor::run()
{
    vector<string> registers;
    bool success = true;
    while(true)
    {
        success = shell->getRequest(registers);
        if(success && registers.size() > 0)
        {
            success = processManager->runCommand(registers);
            registers.clear();
        }

        if(!success)
        {
            std::cout << "-1" << '\n';
        }
    }
}

Processor::~Processor()
{
    shell.release();
    processManager.release();
}