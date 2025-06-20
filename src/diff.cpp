#include "../include/Diff.h"
#include "../include/commitDatabase.h"
#include "../include/Commit.h"

#include <iostream>
#include <unordered_set>
#include <filesystem>
#include <fstream>

extern std::unordered_map <std::string, Commit> commitDatabase;

Commit loadCommitFromDisk(const std::string& hash){
    Commit c;
    c.hash=hash;
    std::string commitDir = ".minigit/commits/"+hash;
    std::ifstream meta(commitDir + "/meta.txt");

    if(!meta.is_open()){
        std::cerr<<"Could not open meta.txt for commit <<hash"<<"\n";
        return c;
    }

    std::string line;
    while(getline(meta,line)){
        if(line.rfind("hash",0)==0) c.message=line.substr(5);
        else if(line.rfind("message",0)==0) c.message=line.substr(8);
        else if(line.rfind("timestamp",0)==0) c.timestamp=line.substr(10);
        else if(line.rfind("parent",0)==0) c.parent=line.substr(7);
    }
    meta.close();

    for(const auto& entry:std::filesystem::directory_iterator(commitDir)){
        std::string filename=entry.path().filename().string();
        if(filename=="meta.txt") continue;
        std::ifstream file(entry.path());
        std::string content ((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        c.files.push_back(filename);
        c.fileContents[filename]=content;    
    }
    return c;
}

void showDiff(const std::string& hash1, const std::string& hash2){
    Commit c1=loadCommitFromDisk(hash1);
    Commit c2=loadCommitFromDisk(hash2);

    if(c1.files.empty() || c2.files.empty()){
        std::cout<<"One or both commits not found\n";
        return;
    }


    std::unordered_set<std::string> files1 (c1.files.begin(), c1.files.end());
    std::unordered_set<std::string> files2 (c2.files.begin(), c2.files.end()); 

    std::cout<<"Comparing commits "<<hash1<<" and"<<hash2<<":\n";

    for(const auto& f:files2){
        if (files1.find(f)==files1.end()){
            std::cout<<"Added: "<<f<<"\n";
        }
    }
    for(const auto& f:files1){
        if (files2.find(f)==files2.end()){
            std::cout<<"Removed: "<<f<<"\n";
        }
    }

    for(const auto& f:files1){
        if (files2.find(f)!=files2.end()){
            std::string content1 = c1.fileContents.at(f);
            std::string content2=c2.fileContents.at(f);
            if(content1!=content2){
                std::cout <<"Modified: "<<f<<"\n";
                std::cout<<" -Old: "<<content1<<"\n";
                std::cout<<" +New: "<<content2<<"\n";
            }
        }
    }

}