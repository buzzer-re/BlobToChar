// #include "Config.h"

#include "FileManager.h"
#include "Argparse.h"

#include <memory>
#include <string>
#include <iostream>


#define BLOB_NAME   "blobname"
#define VAR_NAME    "varname"
#define FILE_NAME   "filename"
#define LINE_NUMBER "linenumber"


void displayHelp() {
    std::cout << "Usage: ./blobBuilder --blobname <blob_path> --varname <variable_name> --linenumber <line_to_insert>\n";
}

int main(int argc, char** argv)
{

    // std::cout << PROJECT_NAME << " " << PROJECT_MAJOR << "." << PROJECT_MINOR << std::endl;
    
    if (argc < 3) {
        displayHelp();
        return 1;
    } 

    ArgParse args(argc, argv);
    args.addArgument(BLOB_NAME, true);
    args.addArgument(VAR_NAME, true);
    args.addArgument(FILE_NAME, true);
    args.addArgument(LINE_NUMBER, true);
    
    if (!args.parse()) return 1;

    FileManager fileManager;
    
    const std::string blobTarget = args.getArgument(BLOB_NAME).argValue;
    std::string varName = args.getArgument(VAR_NAME).argValue;
    std::string insertFile = args.getArgument(FILE_NAME).argValue;
    // std::string lineNumber = args.getArgument(LINE_NUMBER).argValue;
    // int lineNumber_i;

    // if (lineNumber != "") {
    //     try {
    //         lineNumber = std::stoi(lineNumber);
    //     } catch (std::invalid_argument const &e) {
    //         std::cerr << "Line number must be a number!\n";
    //         return 1;
    //     } catch (std::out_of_range const&e) {
    //         std::cerr << "Dud, are u trying overflow me ?\n";
    //         return 1;
    //     }
    // }

    if (fileManager.exists(blobTarget)) {
        std::string codeBuilder;

        codeBuilder = "char " + varName + "[] = ";
        
        std::unique_ptr<ByteArray> fileByteArray(fileManager.toByteArray(blobTarget));

        char* hexRep = new char[4];  // 0xFF
        
        for (auto it = fileByteArray->begin(); it != fileByteArray->end(); ++it) {
            std::sprintf(hexRep, "0x%x",  *it);
            codeBuilder += std::string(hexRep) + ",";
        }

        delete[] hexRep;
        codeBuilder += "};";

    } else {
        std::cerr << "Invalid file " << blobTarget << std::endl;
        return 1;
    }

    return 0;
}
