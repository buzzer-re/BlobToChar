#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include <unistd.h>
#include <getopt.h>


#include <iostream>

/// Struct that represent an argument
struct Argument {
    std::string argName;
    std::string argValue;
    bool required;
    int argIndex;
};


class ArgParse {
public:
    ArgParse(int argc, char* argv[]);
    void parse();

    bool addArgument(const std::string& argument, bool required);
    std::unordered_map<std::string, Argument>& getArgumentMap() const;

private:
    std::unordered_map<std::string, Argument> arguments;
    std::unordered_map<std::string, Argument>::const_iterator argIt;
    int argc;
    char** argv; /// An pointer to argv
};



