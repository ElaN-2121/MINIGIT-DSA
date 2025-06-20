#include "../include/StagingArea.h"
#include "sha1.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

//Adding File to Staging Area

void StagingArea::addFile(const std::string& filename){
    std::ifstream inFile(filename);
    if(!inFile){
        std::cerr <<"Error: Unable to open file "<<filename<<"\n";
        return;
    }
    std::string content((std::istreambuf_iterator<char>(inFile)),std::istreambuf_iterator<char>());
    inFile.close();

    std::string hash=computeHash(content);

    if(!blobExists(hash)){
        saveBlob(hash,content);
        std::cout<<"A new blob added for "<< filename << "->" << hash << "\n";
    }else{
        std::cout<< "File " << filename <<" unchanged. Blob creation is not done.\n";
    }
    stagedFiles[filename] =hash;
    
}

//Showing All Staged Files

void StagingArea::showStagedFiles()const{
    std::cout<< "\nThe Staged Files Are:\n";
    for(const auto& entry:stagedFiles){
        std::cout<< " - " <<entry.first<< "->" <<entry.second<<"\n";
    }
}

//Return the map of staged files
const std::unordered_map<std::string,std::string>& StagingArea::getStagedFiles() const{
    return stagedFiles;
}

//Computing SHA-1 hash using the copied sha1 code from a Public Domain
std::string StagingArea::computeHash(const std::string& content){
    SHA1 sha1;
    sha1.update(content);
    return sha1.final();
}

//Saving files as a Blob
void StagingArea::saveBlob(const std::string& hash, const std::string& content ){
    fs::create_directories(".minigit/objects");

    fs::path blobPath= ".minigit/objects/"+hash;
    std::ofstream out(blobPath);
    if(out){
        out<<content;
        out.close();
    }
}
bool StagingArea::blobExists(const std::string& hash){
    return fs::exists(".minigit/objects/" + hash);
}
