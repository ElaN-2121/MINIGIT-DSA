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

        }
        else if(cmd=="exit"){
            cout<<"Leaving MiniGit....\n";
            break;
        }else{
            cout<<"Unknown command "<<cmd<< " has been entered"<<endl;
        }
    }
    return 0;
}

