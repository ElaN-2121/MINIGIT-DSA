#ifndef COMMIT_H
#define COMMIT_H

#include<string>
#include <vector>
#include <unordered_map>
#include "StagingArea.h"

struct Commit{
    std::string hash;
    std::string message;
    std::string parent;
    std::string timestamp;
    std::vector<std::string> files;
    std::unordered_map<std::string , std::string> fileContents;
};
void commit(const std::string& message, StagingArea& staging);

#endif
