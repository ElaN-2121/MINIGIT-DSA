#include "../include/Reference.h"
#include <fstream>
#include <iostream>
#include "Utils.h"

#ifdef _WIN32
#include <direct.h>
const std::string sep="\\";
#else
#include <sys/stat.h>
const std::string sep="/";
#endif


std::string getHeadCommitHash(){
    Reference ref;
    std::string branch = ref.getHEAD();
    if(branch.empty()) return "";

    std::ifstream branchFile(",minigit/branches/"+branch+".txt");
    std::string commitHash;
    if(branchFile.is_open()){
        std::getline(branchFile,commitHash);
        branchFile.close();
        return trim(commitHash);
    }
    else{
        std::cerr<<"failed to open branch file";
        return "";
    }
}
std::string Reference::getHEAD() {
    std::ifstream headFile(".minigit" +sep+ "HEAD");
    std::string line;
    if (headFile.is_open()) {
        std::getline(headFile, line);
        headFile.close();
        return line;
    } else {
        std::cerr << "Failed to open HEAD file\n";
        return "";
    }
}

void Reference::setHEAD(const std::string& ref) {
    std::ofstream headFile(".minigit" +sep+ "HEAD");
    if (headFile.is_open()) {
        headFile << ref << "\n";
        headFile.close();
    } else {
        std::cerr << "Failed to write HEAD file\n";
    }
}

std::string Reference::getRef(const std::string& refName) {
    std::ifstream refFile( (".minigit" + sep + refName).c_str() );
    std::string hash;
    if (refFile.is_open()) {
        std::getline(refFile, hash);
        refFile.close();
        return hash;
    } else {
        std::cerr << "Failed to open ref file: " << refName << "\n";
        return "";
    }
}

void Reference::setRef(const std::string& refName, const std::string& hash) {
    std::ofstream refFile( (".minigit" + sep + refName).c_str() );
    if (refFile.is_open()) {
        refFile << hash << "\n";
        refFile.close();
    } else {
        std::cerr << "Failed to write ref file: " << refName << "\n";
    }
    
}

