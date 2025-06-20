#include <iostream>
#include <sstream>
#include<string>

#include "Init.h"
#include "StagingArea.h" 
#include "Commit.h"
#include "Blob.h"
#include "Branch.h"
#include "Checkout.h"
#include "Reference.h"
#include "CommitDatabase.h"
#include "Diff.h"
#include "Log.h"

using namespace std;

int main(){
    StagingArea staging;
    cout<<"Welcome to MiniGit! Type \"help\" to see available commands";
    while (true){
        cout<<"#";
        string fullInput;
        getline(cin, fullInput);
        istringstream iss(fullInput);
        string cmd;
        iss>>cmd;

        if(cmd=="init"){
            init();
        }
        else if (cmd=="add"){
            string filename;
            iss>>filename;
            if (filename.empty()){
                cout<<"Please enter a file name to add\n";
            }
            else{
                staging.addFile(filename);
            }
        }
        else if(cmd=="commit"){
            string message;
            getline(iss,message);
            if(message.empty()){
                cout<<"Commit Message Can Not be Empty!\n";
            }
            else{
                if(!message.empty()&&message[0]==' '){
                    message.erase(0,1);
                }commit(message);
            }  
        }
        else if(cmd=="log"){
            std::string headHash=getHEAD();
            printLog(headHash);
        }
        else if(cmd=="checkout"){
            string target;
            iss>>target;
            if(target.empty()){
                cout<<"Please enter a commit hash or branch name to checkout.\n";
            }
            else{
            checkout(target);
            }
        }
        else if(cmd=="diff"){
            string c1,c2;
            iss>>c1>>c2;
            if(c1.empty() || c2.empty()){
                cout<<"Please enter two commits to diff.\n";
            }
            else{
                showDiff(c1,c2);
            }
        }
        else if(cmd=="branch"){
            string branchName;
            iss>>branchName;
            if(branchName.empty()){
                cout<<"Please provide a branch name.\n";
            }
            else{
                createBranch(branchName);
            }
        }
        else if(cmd=="merge"){
            string otherBranch;
            iss>>otherBranch;
            if(otherBranch.empty()){
                cout<<"please provide a branch to merge.\n";
            }
            else{
                mergeBranch(otherBranch);
            }
        }
        else if(cmd=="exit"){
            cout<<"Leaving MiniGit....\n";
            break;
        }
        else if (cmd=="help"){
            cout<<"\nList of Commands: \n"
                <<"init - Initializes a repository\n"
                <<"add<file> - Stages a file\n"
                <<"commit - Commit staged changes\n"
                <<"log - View commit log\n"
                <<"checkout <id> Checkout commit or branch\n"
                <<"diff<c1><c2> - Show file differences\n"
                <<"branch<name> - Create new branch\n"
                <<"merge<branch> Merge branch\n"
                <<"exit - Exits MiniGit\n";
        }
        else{
            cout<<"Unknown command "<<cmd<< " has been entered"<<endl;
        }
    }
    return 0;
}

