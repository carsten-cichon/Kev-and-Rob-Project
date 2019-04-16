#ifndef SERVERREQUEST_INCLUDE
#define SERVERREQUEST_INCLUDE
#include <string>
#include <winsock2.h>
#include <windows.h>
#include "HttpRequest.h"
class ServerRequest
{
private:
    /* data */
    HttpRequest request;
    SOCKET serverSocket;
    std::string serverIpAddr;
    std::string serverPort;
public:
    ServerRequest(/* args */);
    ~ServerRequest();
    std::string getServerIpAddr();
    std::string getServerPort();
    void setServerIpAddr();
    void setServerPort();
};
#endif 