#include <shell/Shell.h>

Shell::Shell(){}


bool Shell::getRequest(vector<string>& command)
{
    // reads input from user into the registers
    readInput(command);
    bool success = true;
    if(command.size() > 0)
    {
        //top level verification of command
        string& commandType = command[0];
        if(commandType == "cr")
            success = this->verifyCreateCommand(command);
        else if (commandType == "de")
            success = this->verifyDestroyCommand(command);
        else if (commandType == "rq")
            success = this->verifyRequestResourceCommand(command);
        else if (commandType == "rl")
            success = this->verifyReleaseResourceCommand(command);
        else if (commandType == "to")
            success = this->verifyTimeoutCommand(command);
        else if (commandType == "in")
            success = this->verifyInitCommand(command);
        else
            success = false;
    }
    return success;
}

void Shell::readInput(vector<string>& command)
{
    //read the line
    string line;
    getline(std::cin, line);
    if(!std::cin)
        exit(EXIT_SUCCESS);
    std::istringstream iss(line);
    std::copy(std::istream_iterator<string>(iss), std::istream_iterator<string>(), std::back_inserter(command));
}

bool Shell::verifyTimeoutCommand(const vector<string>& command) const
{
    return command.size() == 1;
}

bool Shell::verifyDestroyCommand(const vector<string>& command) const 
{
    return command.size() == 2 && verifyIntConversion(command, 1);
}

bool Shell::verifyInitCommand(const vector<string>& command) const
{
    return command.size() == 1;
}

bool Shell::verifyIntConversion(const vector<string>& command, size_t i, size_t j) const
{
    if(i > j || j > command.size() - 1)
        throw std::exception();

    for(size_t k = i; k <= j; ++k)
    {
        if(!verifyIntConversion(command, k))
            return false;
    }
    return true;
}

bool Shell::verifyIntConversion(const vector<string>& command, size_t i) const
{
    if(i > command.size() - 1)
        throw std::exception();
    
    try{
        std::stoi(command[i]);
    } catch (std::exception) {
        return false;
    }
    return true;
}

Shell::~Shell(){}