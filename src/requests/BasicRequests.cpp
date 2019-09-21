#include <requests/BasicRequests.h>

// ---- Create Functions
BasicCreate::BasicCreate(){}

void BasicCreate::setPid(const int newPid)
{
    pid = newPid;
}

std::string BasicCreate::getResponse() const 
{
    std::ostringstream s;
    s << "Process " << pid << " created" << '\n';
    return s.str();
}




// ---- Request Resource functions
BasicRequestResource::BasicRequestResource(int rid) : rid(rid), success(false), blockedProcess(-1)
{}

std::string BasicRequestResource::getResponse() const 
{
    std::ostringstream s;
    if(success)
    {
        s << "Resource " << rid << " allocated" << '\n';
    }
    else 
    {
        s << "Process " << blockedProcess << " blocked" << '\n';
    }
    return s.str();
}

void BasicRequestResource::setSuccess(bool success) 
{
    success = success;
}

void BasicRequestResource::setSuccess(bool success, int pid)
{
    success = success;
    blockedProcess = pid;
}




// ----- Release Requst Functions
BasicReleaseResource::BasicReleaseResource(int rid): rid(rid){}

std::string BasicReleaseResource::getResponse() const
{
    std::ostringstream s;
    s << "Resource " << rid << " released" << '\n';
    return s.str();
}

