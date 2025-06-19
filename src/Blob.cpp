// blob.cpp
#include "../include/Blob.h"
#include "sha1.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

#ifdef _WIN32
#include <direct.h>  // for _mkdir on Windows
#else
#include <sys/stat.h>  // for mkdir on Linux/macOS
#endif


static void createDir(const std::string& path){
    #ifdef _WIN32
        _mkdir(path.c_str());
    #else 
        mkdir(path.c_str(),0777);
    #endif
}

//

// Constructor: reads the file content
Blob::Blob(const std::string& filename) : filename(filename) {
    std::ifstream file(filename.c_str(),std::ios::binary);  // convert string to const char*
    if (file) {
        std::ostringstream ss;
        ss << file.rdbuf();
        content = ss.str();
        hash = SHA1::from_string(content);
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

// Save the content into .minigit/objects/<hash>
void Blob::save() {
    createDir(".mingit");
    createDir(".minigit/objects");

    std::string path = ".minigit/objects/" + hash;
    std::ofstream out(path.c_str(), std::ios::binary);  // also use c_str() here
    if (out) {
        out << content;
        out.close();
        std::cout << "Blob saved with hash: " << hash << std::endl;
    } else {
        std::cerr << "Failed to save blob file." << std::endl;
    }
    
}
//
