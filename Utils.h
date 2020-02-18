#include <iostream>
using namespace std;

class Utils
{
    public:
    static bool getStrArgValue(int argc, char ** argv, const std::string & argument, string & value);
};