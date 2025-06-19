#include "../include/Log.h"
#include "commitDatabase.h"
#include <iostream>


void printLog(const std::string& headHash){
  std::string current=headHash;
  while (!current.empty()){
    const Commit& c=commitDatabase[current];
    std::cout<<"Commit: "<<c.hash<<"\n";
    std::cout<<"Date: "<<c.timestamp<<"\n";
    std::cout<<"Message: "<<c.message<<"\n";
    current=c.parent;
  }
}
