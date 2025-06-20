#include "../include/Commit.h"
#include "../include/StagingArea.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
using namespace std;
namespace fs = std::filesystem;

void commit(const string& message, StagingArea& staging){
    time_t now=time(0);
    string commit_id = to_string(now);
    string commit_folder= ".minigit/commits/" + commit_id;
    fs::create_directories(commit_folder);

    const auto& stagedFiles = staging.getStagedFiles();
    if(stagedFiles.empty()){
        std::cout<<"No staged files to commit.\n";
        return;
    }
    for (const auto& [filename, hash] : stagedFiles){
        std::string blobPath = ".minigit/objects/"+hash;
        std::ifstream in(blobPath,std::ios::binary);
        if(!in) {
            std::cerr<<"error: Blob "<<hash<<" for file "<<filename<<" not found.\n";
            continue;
        }
        std::ofstream out (commit_folder + "/" + filename, std::ios::binary);
        out<<in.rdbuf();
        in.close();
        out.close();
    }
    std::ofstream meta(commit_folder+"/meta.txt");
        if(meta){
            meta<<"hash: "<<commit_id<<"\n";
            meta<<"message: "<<message<<"\n";
            meta<<"timestamp: "<<ctime(&now)<<"\n";
            meta.close();
        }
    

    std::ofstream log(".minigit/log.txt", std::ios::app);
    if (log){
        log<<"Commit: "<<commit_id << "\n";
        log<<"Message: "<<message<< "\n";
        log<< "Date: "<< ctime(&now);
        log<<"-----------------------\n";
        log.close();
    }

    ofstream head(".minigit/HEAD");
    if(head){
        head<<commit_id;
        head.close();
    }

    cout<<"Committed successfully with ID "<< commit_id<<endl;
}
