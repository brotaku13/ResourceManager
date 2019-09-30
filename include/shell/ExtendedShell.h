#ifndef EXTENDED_SHELL_H
#define EXTENDED_SHELL_H

#include <shell/Shell.h>

class ExtendedShell : public Shell 
{
public:
    ExtendedShell();

    bool verifyCreateCommand(const vector<string>& command) const;
    bool verifyRequestResourceCommand(const vector<string>& command) const;
    bool verifyReleaseResourceCommand(const vector<string>& command) const;

    ~ExtendedShell();

private:
    

};

#endif