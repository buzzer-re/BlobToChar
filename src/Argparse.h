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
    bool required_arg;
    int argIndex;
};


class ArgParse {
public:
    ArgParse(int argc, char* argv[]);
    bool parse();
    /// required an argument and if its requried to be passed
    bool addArgument(const std::string& argument, bool required_arg, bool required);
    std::unordered_map<std::string, Argument>& getArgumentMap() const;
    
    Argument& getArgument(const std::string& argument);

private:
    std::unordered_map<std::string, Argument> arguments;
    std::unordered_map<std::string, Argument>::iterator argIt;
    int argc;
    char** argv; /// An pointer to argv
};



