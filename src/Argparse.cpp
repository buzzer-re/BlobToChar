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


/// take a look at the while loop
void ArgParse::parse() 
{         
    struct option long_options[this->arguments.size()];

    int arg;
    int op_i = 0;
    /// fill long options with our arguments
    for (argIt = arguments.begin(); argIt != arguments.end(); ++argIt, ++op_i) {
        std::cout << argIt->first.c_str();
        long_options[op_i] = {
            argIt->first.c_str(), argIt->second.required, 0, argIt->first.at(0)
        };
    }

    op_i = 0; // reset var for other loop
    // parse argv using getotp
    while ((arg = getopt_long(this->argc, this->argv, "abc:d:f:", long_options, &op_i)) != -1) {
        switch(arg) {

            // case 'v': 
            //     std::cout << "--varname passed!\n";

        }
    }
}