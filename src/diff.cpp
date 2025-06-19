#include "../include/Diff.h"
#include "../include/commitDatabase.h"
#include <iostream>
#include <unordered_set>

extern std::unordered_map <std::string, commit> commitDatabase;

void showDiff(const std::string& hash1, const std::string& hash2){
    if (commitDatabase.find(hash1)==commitDatabase.end()||commitDatabase.find(hash2)==commitDatabase.end()){
        std::cout<<"One or both commits not found.\n";
        return;
    }
    Commit c1=commitDatabase[hash1];
    Commit c2=commitDatabase[hash2];

    std::unordered_set<std::string> files1 (c1.files.begin(), c1.files.end());
    std::unordered_set<std::string> files2 (c2.files.begin(), c2.files.end()); 

    std::cout<<"Comparing commits "<<hash1<<" and"<<hash2<<":\n";

    for(const auto& f:files2){
        if (files1.find(f)==files1.end()){
            std::cout<<"Added: "<<f<<"\n";
        }
    }

    for(const auto& f:files1){
        if (files2.find(f)!=files2.end()){
            std::string content1 = c1.fileContents.at(f);
            std::string content2=c2.fileContents.at(f);
            if(content1!=content2){
                std::cout <<"Modified: "<<f<<"\n";
                std:cout<<" -Old: "<<content1<<"\n";
                std::cout<<" +New: "<<content2<<"\n";
            }
        }
    }

}