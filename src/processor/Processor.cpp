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
        shell = nullptr;
        processManager = nullptr;
    }
}

void Processor::run()
{
    vector<string> registers;
    bool success = true;
    while(success)
    {
        success = shell->getRequest(registers);
        if(success)
        {
            success = processManager->runCommand(registers);
            registers.clear();
        }

        if(!success)
        {
            std::cout << "error" << '\n';
        }
    }
}

Processor::~Processor()
{
    shell.release();
    processManager.release();
}