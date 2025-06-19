#include "reference.h"
#include <fstream>

#include <iostream>

std::string Reference::getHEAD() {
	
    std::ifstream headFile(".minigit/HEAD");
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
    std::ofstream headFile(".minigit/HEAD");
    if (headFile.is_open()) {
        headFile << ref << "\n";
        headFile.close();
    } else {
        std::cerr << "Failed to write HEAD file\n";
    }
}

std::string Reference::getRef(const std::string& refName) {
    std::ifstream refFile( (".minigit/" + refName).c_str() );
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
    std::ofstream refFile( (".minigit/" + refName).c_str() );
    if (refFile.is_open()) {
        refFile << hash << "\n";
        refFile.close();
    } else {
    	
        std::cerr << "Failed to write ref file: " << refName <<"\n";
    }
    
}
//

