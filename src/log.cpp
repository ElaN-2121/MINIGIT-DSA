#include <iostream>
#include <fstream>
#include <string>

void printLog(const std::string& headHash) {
    std::ifstream logFile(".minigit/log.txt");
    if (!logFile) {
        std::cerr << "Could not open log file.\n";
        return;
    }

    std::string line;
    while (std::getline(logFile, line)) {
        std::cout << line << std::endl;
    }

    logFile.close();
}
