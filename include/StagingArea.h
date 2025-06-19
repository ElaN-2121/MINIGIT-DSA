#ifndef STAGING_AREA_H
#define STAGING_AREA_H
#include <unordered_map>
#include <string>


class StagingArea{
public:
    void addFile(const std::string& filename);
    void showStagedFiles() const;

    const std::unordered_map<std::string, std::string>& getStagedFiles() const;
private:
    std::string computeHash(const std::string& filepath);
    std::unordered_map<std::string,std::string> stagedFiles;
    void saveBlob(const std::string& hash,const std::string& content);
    bool blobExists(const std::string& hash);

};
#endif