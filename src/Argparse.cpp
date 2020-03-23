#include "Argparse.h"


ArgParse::ArgParse(int argc, char* argv[])
{
    this->argc = argc;
    this->argv = argv;
}


bool ArgParse::addArgument(const std::string& argument, bool required) 
{
    argIt = this->arguments.find(argument);

    if (argIt != this->arguments.end() )
        return false;

    Argument newArgument{argument,"", required};

    this->arguments.insert(std::make_pair(argument, newArgument));

    return true;
}


bool ArgParse::parse() 
{         
    struct option long_options[this->arguments.size()];

    int arg = 0;
    int op_i = 0;
    /// fill long options with our arguments
    for (argIt = arguments.begin(); argIt != arguments.end(); ++argIt, ++op_i) {
        long_options[op_i] = {
            argIt->first.c_str(), argIt->second.required, 0, argIt->first.at(0)
        };
    }

    op_i = 0; // reset var for other loop
    // parse argv using getotp
    while ((arg = getopt_long(this->argc, this->argv, "abc:d:f:", long_options, &op_i)) != -1) {
        if (arg == '?') return false;

        
        std::string argumentName = long_options[op_i].name;
        this->argIt = this->arguments.find(argumentName);
        
        argIt->second.argValue = optarg;
        argIt->second.argIndex = op_i;
    }
    
    return true;
}


/// Throws error if the argument does not was inserted before
Argument& ArgParse::getArgument(const std::string& argument) 
{
    this->argIt = this->arguments.find(argument);

    if (argIt == this->arguments.end()) 
        throw ("Unable to find argument ");

    return argIt->second;
}