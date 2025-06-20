#include "../include/Log.h"
#include "commitDatabase.h"
#include <iostream>
#include <fstream>
#include "Utils.h"

void printLog(const std::string& headHash){
  std::string current=headHash;
  while (!current.empty()){
    std::ifstream fin(".minigit/commits/" + current+"/meta.txt");
    if (!fin.is_open()) break;

    std::string line, hash, date, message, parent;
    while (getline(fin,line)){
      if(line.rfind("hash",0)==0) hash=trim(line.substr(5));
      else if (line.rfind("timestamp",0)==0) date=trim(line.substr(10));
      else if (line.rfind("message",0)==0) message=trim(line.substr(8));
      else if (line.rfind("parent",0)==0) parent=trim(line.substr(7));    
    }
    std::cout<<"Commit: "<<hash<<"\n";
    std::cout<<"Date: "<<date<<"\n";
    std::cout<<"Message: "<<message<<"\n\n";
    if(parent.empty()||parent=="none")break;
    current=parent;
  }
}
