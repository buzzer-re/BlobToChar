#pragma once

#include <string>
#include <vector>

#include <unistd.h>



/// Struct that represent an argument
struct Argument {
    std::string argName;
    std::string argValue;
    int argIndex;
};


class ArgParse {
public:
    ArgParse(int argc, char* argv[]);
    void parse();

    std::vector<Argument>& getArgumentVector() const;
private:
    std::vector<Argument> arguments;
};



