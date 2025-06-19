// init.cpp
#include <iostream>
#include <fstream>
#include <direct.h>  

void init() {
  
    _mkdir(".minigit");
    _mkdir(".minigit\\objects");
    _mkdir(".minigit\\refs");
    _mkdir(".minigit\\refs\\heads");

   
    std::ofstream head(".minigit\\HEAD");
    if (head.is_open()) {
        head << "ref: refs/heads/master\n";
        head.close();
    } else {
        std::cerr << "Failed to create HEAD file.\n";
        return;
    }


    std::ofstream master(".minigit\\refs\\heads\\master");
    if (master.is_open()) {
    	
        master << "";  
        master.close();
    } else {
    	
        std::cerr << "Failed to create master branch file.\n";
        return;
        
    }

    std::cout << ".minigit initialized.\n";
}

