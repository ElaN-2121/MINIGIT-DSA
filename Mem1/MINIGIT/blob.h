// blob.h
#ifndef BLOB_H
#define BLOB_H

#include <string>

class Blob{
public:
    Blob(const std::string& filename);
    void save();

private:
    std::string content;
    std::string hash;
    std::string filename;
    std::string calculateHash(const std::string& data);
    
    
};

#endif


//
