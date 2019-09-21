#include <shell/Shell.h>

Shell::Shell() : currentRequest(0){}

void Shell::reset()
{
    if(currentRequest)
        delete currentRequest;
}

Request* Shell::getRequest()
{
// reads input, validates input, creates new request
    reset();
    vector<string> command;
    readInput(command);

    Request *newRequest = nullptr;

    if(command.size() > 0)
    {
        bool success = true;
        string& commandType = command[0];
        if(commandType == "cr")
        {
            if(this->verifyCreateCommand(command))
            {
                this->initCreateRequest(command);
            }
            else 
                success = false;
        }
        else if (commandType == "de")
        {
            if(this->verifyDestroyCommand(command))
            {
                newRequest = this->initDestroyRequest(command);
            }
            else
                success = false;
            
        }
        else if (commandType == "rq")
        {
            if(this->verifyRequestResourceCommand(command))
            {
                newRequest = this->initRequestResourceRequest(command);
            }
            else
                success = false;
        }
        else if (commandType == "rl")
        {
            if(this->verifyReleaseResourceCommand(command))
            {
                newRequest = this->initReleaseResourceRequest(command);
            }
            else
             success = false;
            
        } 
        else if (commandType == "to")
        {
            if(this->verifyTimeoutCommand(command))
            {
                newRequest = this->initTimeoutRequest();
            }
            else
                success = false;
        }
        else if (commandType == "in")
        {
            if(this->verifyInitCommand(command))
            {
                newRequest = this->initInitRequest();
            }
            else
                success = false;
        } 
        else 
        {
            success = false;
        }
        
        if(!success)
        {
            printError();
        }
    }
    else
    {
        //we failed to receive a command, error out
        printError();
    }
    
    currentRequest = newRequest;

    return newRequest;
}

void Shell::readInput(vector<string>& command)
{
    //read the line
    string line;
    getline(std::cin, line);
    istringstream iss(line);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(command));
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

void Shell::printError()
{
    cout << "error" << '\n';
}

Request* Shell::initDestroyRequest(const vector<string>& command) const 
{
    return new DestroyRequest(std::stoi(command[1]));
}

Request*  Shell::initInitRequest() const 
{
    return new InitRequest();
}

Request*  Shell::initTimeoutRequest() const 
{
    return new TimeoutRequest();
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
        int n = std::stoi(command[i]); ++n;
    } catch (std::exception) {
        return false;
    }
    return true;
}

Shell::~Shell()
{
    if(currentRequest)
        delete currentRequest;
}