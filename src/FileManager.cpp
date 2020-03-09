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