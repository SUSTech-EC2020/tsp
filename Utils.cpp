#include "Utils.h"

bool Utils::getStrArgValue(int argc, char ** argv, const std::string & argument, std::string & value)
{
    bool isFound = false;
    for(int i = 0 ; i < argc - 1 ; i++)
    if(std::string(argv[i]) == ("-" + argument)) {
        value = string(argv[i + 1]);
        isFound = true;
    }
    return isFound;
}