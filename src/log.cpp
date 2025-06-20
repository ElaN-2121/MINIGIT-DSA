#include "../include/Log.h"
#include "commitDatabase.h"
#include <iostream>
#include <fstream>


void printLog(const std::string& headHash){
  std::string current=headHash;
  while (!current.empty()){
    std::ifstream fin(".minigit/commits/" + current);
    if (!fin.is_open()) break;

    std::string line, hash, date, message, parent;
    while (getline(fin,line)){
      if(line.rfind("hash",0)==0) hash=line.substr(5);
      else if (line.rfind("timestamp",0)==0) date=line.substr(10);
      else if (line.rfind("message",0)==0) message=line.substr(8);
      else if (line.rfind("parent",0)==0) parent=line.substr(7);    
    }
    std::cout<<"Commit: "<<hash<<"\n";
    std::cout<<"Date: "<<timestamp<<"\n";
    std::cout<<"Message: "<<message<<"\n\n";
    current=parent;
  }
}
