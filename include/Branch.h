#ifndef BRANCHING_H
#define BRANCHING_H
#include <string>
#include <unordered_map>

std::string getHEAD();
void setHEAD(const std::string &ref);
std::string getCommitHash(const std::string &refName);
std::string getParent (const std::string &commitHash);

std::unordered_map<std::string, std::string> loadCommitBlobs(const std::string &commitHash);

void createBranch(const std::string &branchName);
void checkout(const std::string &target);

std::string findLCA(std::string a, std::string b);
void mergeBranch(const std::string &otherBranch);
#endif