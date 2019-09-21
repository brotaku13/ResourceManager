#ifndef BASIC_SHELL_H
#define BASIC_SHELL_H

#include <shell/Shell.h>
#include <requests/BasicRequests.h>

class BasicShell : public Shell {
public:
    BasicShell();
    bool verifyCreateCommand(const vector<string>& command) const;
    bool verifyReleaseResourceCommand(const vector<string>& command) const;
    bool verifyRequestResourceCommand(const vector<string>& command) const;

    Request*  initCreateRequest(const vector<string>& command) const;
    Request*  initRequestResourceRequest(const vector<string>& command) const;
    Request*  initReleaseResourceRequest(const vector<string>& command) const;

    ~BasicShell();
};

#endif