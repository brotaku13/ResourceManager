#ifndef BASIC_SHELL_H
#define BASIC_SHELL_H

#include <shell/Shell.h>

class BasicShell : public Shell {
public:
    BasicShell();
    bool verifyCreateCommand(const vector<string>& command) const;
    bool verifyReleaseResourceCommand(const vector<string>& command) const;
    bool verifyRequestResourceCommand(const vector<string>& command) const;
    ~BasicShell();
};

#endif