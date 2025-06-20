#ifndef Diff_H
#define DIFF_H

#include <string>
#include "Commit.h"

Commit loadCommitFromDisk(const std::string& hash);
void showDiff(const std::string& hash1, const std::string& hash2);

#endif