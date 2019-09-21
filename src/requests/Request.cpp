#include <requests/Request.h>

// ---- Destroy functions
DestroyRequest::DestroyRequest(int pid) : pid(pid)
{
    nProcesses = 0;
}

void DestroyRequest::setNProcessesDestroyed(int n)
{
    nProcesses = n;
}

std::string DestroyRequest::getResponse() const 
{
    std::ostringstream s;
    s << nProcesses << " processes destroyed" << '\n';
    return s.str();
}




// ---- Timeout Request functions
TimeoutRequest::TimeoutRequest(){}

void TimeoutRequest::setCurrentProcess(int pid)
{
    currentProcess = pid;
}

std::string TimeoutRequest::getResponse() const
{
    std::ostringstream s;
    s << "Process " << currentProcess << " running" << '\n';
    return s.str();
}




// ---- InitRequest functions
InitRequest::InitRequest(){}

std::string InitRequest::getResponse() const
{
    return "";
}
