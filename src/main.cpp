#include "FileManager.h"

#include <memory>
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
    FileManager fileManager;

    const std::string blobTarget = argv[1];
    

    if (fileManager.exists(blobTarget)) {
        std::string codeBuilder;

        codeBuilder = "char* v1= {";
        
        std::unique_ptr<ByteArray> fileByteArray(fileManager.toByteArray(blobTarget));

    }


    return 0;
}
