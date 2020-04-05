#include "FileManager.h"


inline bool FileManager::exists(const std::string& fPath) const
{
    return access(fPath.c_str(), F_OK) != -1;
}


inline unsigned int FileManager::getSize(const std::string& fPath) const
{
    if (!this->exists(fPath)) return 0;

    struct stat st;

    stat(fPath.c_str(), &st);

    return st.st_size;
}


ByteArray* FileManager::toByteArray(const std::string& fPath) const 
{
    if (this->exists(fPath)) {
        ByteArray* bytearray = new ByteArray;
        bytearray->reserve(this->getSize(fPath));
        
        std::ifstream fileStream(fPath, std::ifstream::ios_base::binary);


        while (fileStream) {
            unsigned char uniqueByte;
            fileStream.read((char*) &uniqueByte, sizeof(unsigned char));
            bytearray->push_back(uniqueByte);
        }

        return bytearray;
    }

    return nullptr;
}


int FileManager::insertMiddleFile(const std::string& value, const std::string& fPath, int lineNumber) const
{

    if (!this->exists(fPath)) {
        return BAD_FILE;
    }

    int lineCount = 0;
    unsigned offset = 0;
    std::string stemp;
    
    unsigned fSize = this->getSize(fPath);
    std::fstream fst(fPath);

    while (lineCount != lineNumber)
    {
        std::getline(fst, stemp);
        if (!fst.eof()) {
            offset += stemp.size() + 1;
            lineCount++;
            continue;
        }
        std::cout << offset << std::endl;
        return INVALID_NUM;
    }

    fSize -= offset;
    char* contentBuff = new char[fSize];

    fst.seekp(offset, fst.beg);
    fst.read(contentBuff, fSize);
    contentBuff[fSize] = 0x00;

    fst.seekp(offset, fst.beg);
    fst << value;
    fst << contentBuff;

    delete[] contentBuff;
    fst.close();

    return GOOD;
}