#ifndef HTTPREQUEST_INCLUDE
#define  HTTPREQUEST_INCLUDE

#include <string>

class HttpRequest
{
private:
    /* data */
    std::string method = "";
    std::string url = "";
    std::string body = "";
public:
    HttpRequest(/* args */);
    ~HttpRequest();
    std::string getBody();
    std::string getUrl();
    std::string getMethod();
    std::string buildRequest();
    void setBody(std::string);
    void setUrl(std::string);
    void setMethod(std::string);
};
#endif