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