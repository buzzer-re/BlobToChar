#include "FileManager.h"

#include <memory>
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
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
