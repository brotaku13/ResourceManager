#ifndef SHELL_H
#define SHELL_H

#include <requests/Request.h>
#include <requests/BasicRequests.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

class Shell {
public:
    Shell();
    Request* getRequest();
    void readInput(vector<string>& command);
    void reset();
    void printError();
    bool verifyIntConversion(const vector<string>& command, size_t i, size_t j) const;
    bool verifyIntConversion(const vector<string>& command, size_t i) const;

    //functions that differ
    virtual bool verifyCreateCommand(const vector<string>& command) const = 0;
    virtual bool verifyRequestResourceCommand(const vector<string>& command) const = 0;
    virtual bool verifyReleaseResourceCommand(const vector<string>& command) const = 0;
    //functions that are the same across shells
    bool verifyTimeoutCommand(const vector<string>& command) const;
    bool verifyDestroyCommand(const vector<string>& command) const;
    bool verifyInitCommand(const vector<string>& command) const;

    //functions that differ
    virtual Request* initCreateRequest(const vector<string>& command) const = 0;
    virtual Request* initRequestResourceRequest(const vector<string>& command) const = 0;
    virtual Request* initReleaseResourceRequest(const vector<string>& command) const = 0;
    //functions that are the same across shells
    Request* initDestroyRequest(const vector<string>& command) const;
    Request* initTimeoutRequest() const;
    Request* initInitRequest() const;



    
    ~Shell();

private:
    Request* currentRequest;
};

#endif