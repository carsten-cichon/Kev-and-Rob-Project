#ifndef JSONBUILDER_INCLUDE
#define JSONBUILDER_INCLUDE
#include <string>
class JSONBuilder
{
private:
    std::string content;
public:
    std::string parseJSON(std::string);
    JSONBuilder();
    ~JSONBuilder();
};
#endif
