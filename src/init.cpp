// init.cpp
#include <iostream>
#include <fstream>
#include "../include/init.h"

#ifdef _WIN32
#include <direct.h>
const std::string sep="\\";
#else
#include <sys/stat.h>
const std::string sep="/";
#endif

void createDir(const std::string& path){
    #ifdef _WIN32
        _mkdir(path.c_str());
    #else   
        mkdir(path.c_str(),0777);
    #endif
}


void init() {
    // Create .minigit and subdirectories
    createDir(".minigit");
    createDir(".minigit" +sep+ "objects");
    createDir(".minigit" +sep+ "refs");
    createDir(".minigit" +sep+ "refs" +sep+ "heads");

    // Create HEAD file pointing to master
    std::ofstream head(".minigit" +sep+ "HEAD");
    if (head.is_open()) {
        head << "ref: refs/heads/master\n";
        head.close();
    } else {
        std::cerr << "Failed to create HEAD file.\n";
        return;
    }

    // Create an empty master branch file
    std::ofstream master(".minigit" +sep+ " refs" +sep+ "heads" +sep+ "master");
    if (master.is_open()) {
        master << "";  // Empty, no commits yet
        master.close();
    } else {
        std::cerr << "Failed to create master branch file.\n";
        return;
    }

    std::cout << ".minigit initialized.\n";
}

