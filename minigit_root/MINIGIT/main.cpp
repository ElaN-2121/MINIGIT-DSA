#include <iostream>
#include <windows.h>      
#include "blob.h"

#include "reference.h"


void init();  //init function


std::string getCurrentDir() {
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    return std::string(buffer);
    
}

int main() {
    std::cout << "Running MiniGit Init...\n";

   
    std::cout << "Current working directory: " << getCurrentDir() << std::endl;

    init();


    std::string testFile = "test.txt";  
    Blob blob(testFile);
    blob.save();

    return 0;
    
    
}
//
