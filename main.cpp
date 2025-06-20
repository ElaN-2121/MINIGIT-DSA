#include <iostream>
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
    string cmd;
    while (true){
        cout<<"#";
        getline(cin, cmd);

        if(cmd=="init"){
            init();
        }
        else if (cmd=="add"){
            string filename;
            cin>>filename;
            StagingArea staging;
            staging.addFile(filename);
        }
        else if(cmd=="commit"){
            string message;
            cin.ignore();
            getline(cin, message);
            commit(message);
        }
        else if(cmd=="log"){
            std::string headHash=getHEAD();
            printLog(headHash);
        }
        else if(cmd=="checkout"){
            string target;
            cin>>target;
            checkout(target);
        }
        else if(cmd=="diff"){
            string c1,c2;
            cin>>c1>>c2;
            showDiff(c1,c2);
        }
        else if(cmd=="branch"){
            string branchName;
            cin>>branchName;
            createBranch(branchName);
        }
        else if(cmd=="merge"){
            string otherBranch;
            cin>>otherBranch;
            mergeBranch(otherBranch);
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

