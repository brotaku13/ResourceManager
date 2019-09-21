#ifndef BASIC_REQUEST_H
#define BASIC_REQUEST_H

#include <requests/Request.h>

class BasicCreate : public Request {
public:
    BasicCreate();
    std::string getResponse() const;
    void setPid(const int pid);

    ~BasicCreate(){}
private:
    int pid;
};



class BasicRequestResource : public Request {
public:
    BasicRequestResource(int rid);
    std::string getResponse() const;
    void setSuccess(bool success);
    void setSuccess(bool success, int pid);
    ~BasicRequestResource(){}
private:
    int rid;
    bool success;
    int blockedProcess;
};

class BasicReleaseResource : public Request {
public:
    BasicReleaseResource(int rid);
    std::string getResponse() const;
    ~BasicReleaseResource(){}
private:
    int rid;
};

#endif