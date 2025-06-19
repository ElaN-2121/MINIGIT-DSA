#include "../include/Checkout.h"
#include "commitDatabase.h"
#include <iostream>

void checkoutCommit(const std::string& hash){
  auto it=commitDatabase.find(hash);
  if (it==commitDatabase.end()){
    std::cout<<"Error: No commit  found!!\n";
    return;
  }
  const Commit& c=it->second;
  HEAD = c.hash;
  std::cout<< "Checkedout Commit "<< c.hash <<"\n";
  std::cout<<"Restored Files:\n";
  for (const auto& file :c.files){
    std::cout<<" "<< file <<": "<<c.fileContents.at(file)<<"\n";
  }
  std::cout <<"\n HEAD is now at "<<HEAD<<\n;
} 
