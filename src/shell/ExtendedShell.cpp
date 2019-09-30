#include <shell/ExtendedShell.h>

ExtendedShell::ExtendedShell(){}

ExtendedShell::~ExtendedShell(){}

bool ExtendedShell::verifyReleaseResourceCommand(const vector<string>& command) const
{
    //needs fixing
    return command.size() == 3 && verifyIntConversion(command, 1, 2);
}

bool ExtendedShell::verifyRequestResourceCommand(const vector<string>& command) const
{
    //needs fixing
    return command.size() == 3 && verifyIntConversion(command, 1, 2);
}

bool ExtendedShell::verifyCreateCommand(const vector<string>& command) const
{
    return command.size() == 2 && verifyIntConversion(command, 1);
}