#pragma once
#include <string>

class Trimmer
{
public:

    static std::string trim(std::string s)
    {
        s.erase(0, s.find_first_not_of("\t\n\v\f\r ")); // left trim
        s.erase(s.find_last_not_of("\t\n\v\f\r ") + 1); // right trim

        return s;
    }
};

