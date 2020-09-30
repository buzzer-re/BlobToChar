#include "FileManager.h"
#include "Argparse.h"

#include <memory>
#include <string>
#include <iostream>
#include <type_traits>

#define BLOB_NAME   "blobname"
#define VAR_NAME    "varname"
#define FILE_NAME   "filename"
#define LINE_NUMBER "linenumber"

int displayHelp(const char* progName) {

    return std::fprintf(stderr, "Usage: %s [options]\n\n--blobname\tName of the binary file\n--filename\tName of the target source\n--linenumber\tNumber to insert\n--varname\tvariable name inside code\n", progName);
}


int main(int argc, char** argv)
{
    
    if (argc < 3) {
        return displayHelp(argv[0]);
    } 

    ArgParse args(argc, argv);
    /// addArgument(argName, require_value, require_be_passed)
    args.addArgument(BLOB_NAME, true, true);
    args.addArgument(VAR_NAME, true, false);
    args.addArgument(FILE_NAME, true, false);
    args.addArgument(LINE_NUMBER, true, false);
    
    if (!args.parse()) {
        return displayHelp(argv[0]);
    }

    FileManager fileManager;
    
    const std::string blobTarget       = args.getArgument(BLOB_NAME).argValue;
    std::string varName                = args.getArgument(VAR_NAME).argValue;
    const std::string insertFile       = args.getArgument(FILE_NAME).argValue;
    const std::string lineNumber       = args.getArgument(LINE_NUMBER).argValue;
    
    int lineNumber_i;
    
    if (lineNumber != "") {
        try {
            lineNumber_i = std::stoi(lineNumber) - 1;
        } catch (std::invalid_argument const &e) {
            std::cerr << "Line number must be a number!\n";
            return 1;
        } catch (std::out_of_range const&e) {
            std::cerr << "Dud, are u trying overflow me ?\n";
            return 1;
        } 
    }

    varName = varName == "" ? "buff" : varName;
    
    if (fileManager.exists(blobTarget)) {
        std::string codeBuilder;
        codeBuilder = "unsigned char " + varName + "[] = {";
        std::unique_ptr<ByteArray> fileByteArray(fileManager.toByteArray(blobTarget));

        char* hexRep = new char[4];  // 0xFF

        for (auto it = fileByteArray->begin(); it != fileByteArray->end(); ++it) {
            std::sprintf(hexRep, "0x%x",  *it);
            codeBuilder += std::string(hexRep) + ",";
        }

        codeBuilder.append("};\n"); 
        codeBuilder.append("unsigned int " + varName + "_size = ");
        codeBuilder.append(std::to_string(fileByteArray->size()));
        codeBuilder.append(";\n");
        delete[] hexRep;

        if (insertFile != "") {
            int err = fileManager.insertMiddleFile(codeBuilder, insertFile, lineNumber_i);

            if (err == fileManager.GOOD) {
                std::cout << "New variable " << varName << " inserted with success in line " << lineNumber_i << " of the file " << insertFile << std::endl;
            } else {
                std::cerr << "Unable to insert value in file " << insertFile << std::endl;

                std::cout << "Err: ";
                switch(err) {
                    case fileManager.BAD_FILE:
                        std::cerr << "File does not exist!\n";break;
                    case fileManager.INVALID_NUM:
                        std::cerr << "Invalid line number!\n";break;
                }

                std::cerr << "Press enter to display the value in stdout\n";
                getchar();
                std::cout << codeBuilder << std::endl;
            }
        } else {
            std::cout << codeBuilder << std::endl;
        }


    } else {
        std::cerr << "Invalid blob or inserted file "  << std::endl;
        return 1;
    }

    return 0;
}

