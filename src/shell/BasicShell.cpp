#include <shell/BasicShell.h>



BasicShell::BasicShell(){}

BasicShell::~BasicShell(){}

bool BasicShell::verifyReleaseResourceCommand(const vector<string>& command) const
{
    return command.size() == 2 && verifyIntConversion(command, 1);
}

bool BasicShell::verifyRequestResourceCommand(const vector<string>& command) const
{
    return command.size() == 2 && verifyIntConversion(command, 1);
}

bool BasicShell::verifyCreateCommand(const vector<string>& command) const
{
    return command.size() == 1;
}

Request*  BasicShell::initCreateRequest(const vector<string>& command) const
{
    return new BasicCreate();
}

Request*  BasicShell::initRequestResourceRequest(const vector<string>& command) const
{
    return new BasicRequestResource(std::stoi(command[1]));
}

Request*  BasicShell::initReleaseResourceRequest(const vector<string>& command) const
{
    return new BasicReleaseResource(std::stoi(command[1]));
}