#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <sstream> 

class Request {
public:
    virtual std::string getResponse() const = 0;
    virtual ~Request(){};
};

class DestroyRequest : public Request {
public: 
    DestroyRequest(int pid);
    std::string getResponse() const;
    void setNProcessesDestroyed(int n);
    ~DestroyRequest(){}
private:
    int pid;
    int nProcesses;
};

class TimeoutRequest : public Request {
public:
    TimeoutRequest();
    std::string getResponse() const;
    void setCurrentProcess(int pid);
    ~TimeoutRequest(){}
private:
    int currentProcess;
};

class InitRequest : public Request {
public:
    InitRequest();
    std::string getResponse() const;
    ~InitRequest(){}
};

#endif
