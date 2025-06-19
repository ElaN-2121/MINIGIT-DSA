#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
using namespace std;
namespace fs = std::filesystem;

void commit(string message){
    time_t now= time(0);
    string commit_id = to_string(now);
    string commit_folder= "vcs/commits/" + commit_id;
    fs::create_directories(commit_folder);
    
    string staging_folder="vcs/staging";
    if(!fs::exists(staging_folder) || fs::is_empty(staging_folder)){
        cout<<"No staged files to commit.\n";
        return;
    }
    for(const auto& entry : fs::directory_iterator(staging_folder)){
        fs::copy_file(entry.path(),commit_folder + "/" + entry.path().filename().string(), fs::copy_options::overwrite_existing);
    }
    ofstream log("vcs/log.txt", ios::app);
    log<<"Commit: "<<commit_id << "\n";
    log<<"Message: "<<message<< "\n";

    char* dt= ctime(&now);
    log<< "Date: "<< dt;
    log<<"-----------------------\n";
    log.close();
    cout<<"Committed successfully with ID "<< commit_id<<endl;

}
