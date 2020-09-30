#pragma once


#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



typedef std::vector<unsigned char> ByteArray;

class FileManager 
{
public:
    bool exists(const std::string& fPath) const;
    inline unsigned int getSize(const std::string& fPath) const;

    ByteArray* toByteArray(const std::string& fPath) const;

    int insertMiddleFile(const std::string& value, const std::string& fPath, int lineNumber) const;
private:
    std::string basePath;

public:
    enum err_enum {BAD_FILE, GOOD, INVALID_NUM};
};

