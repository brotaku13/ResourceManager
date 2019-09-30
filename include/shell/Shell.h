#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

using std::vector;
using std::string;

class Shell {
public:
    Shell();
    bool getRequest(vector<string>& command);
    void readInput(vector<string>& command);
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

    
    virtual ~Shell();

private:
    
};

#endif