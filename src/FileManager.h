#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



typedef std::vector<unsigned char> ByteArray;

class FileManager 
{
public:
    inline bool exists(const std::string& fPath) const;
    inline unsigned int getSize(const std::string& fPath) const;

    ByteArray* toByteArray(const std::string& fPath) const;
private:
    std::string basePath;
};

