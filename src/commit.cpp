#include "../include/Commit.h"
#include "../StagingArea.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
using namespace std;
namespace fs = std::filesystem;

void commit(const string& message, StagingArea& staging){
    time_t ow=time(0);
    string commit_id = to_string(now);
    string commit_folder= ".minigit/commits/" + commit_id;
    fs::create_directories(commit_folder);

    const auto& stagedFiles = stagingArea.getStagedFiles();
    if(stagedFiles.empty()){
        std::cot<<"No staged files to commit.\n";
        return;
    }
    for (const auto& [filename, hash] : stagedFiles){
        std::string blobPath, std::ios::binary);
        if(!in) {
            std::cerr<<"error: Blob "<<hash<<" for file "<<filename<<" not found.\n";
            continue;
        }
        std::ofstream out (commit_folder + "/" + filename, std::ios::binary);
        out<<in.rdbuf();
        in.close();
        out.close();
    }
    
    std::ofstream log(".minigit/log.txt", std::ios::app);
    log<<"Commit: "<<commit_id << "\n";
    log<<"Message: "<<message<< "\n";
    log<< "Date: "<< dctime(&now;
    log<<"-----------------------\n";
    log.close();
    cout<<"Committed successfully with ID "<< commit_id<<endl;

}
