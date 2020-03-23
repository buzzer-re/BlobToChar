#include "FileManager.h"
#include "Argparse.h"

#include <memory>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{
    ArgParse args(argc, argv);
    args.addArgument("--varname", true);
    args.addArgument("--output", true);
    args.addArgument("--insert-line", true);
    args.parse();
    FileManager fileManager;

    
    const std::string blobTarget = argv[1];
    
    std::string varName = argv[2];
    
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

    }


    return 0;
}
