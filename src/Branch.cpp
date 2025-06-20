#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <unordered_map>
#include <set>
#include <ctime>
#include <functional>

namespace fs = std::filesystem;

using namespace std;

std::string getHEAD() {
    ifstream fin(".minigit/HEAD");
    string line;
    getline(fin, line);
    return line;
}


void setHEAD(const string &ref) {
    ofstream fout(".minigit/HEAD");
    fout << ref;
}


string getCommitHash(const string &refName) {
    ifstream fin(".minigit/refs/heads/" + refName);
    string hash;
    getline(fin, hash);
    return hash;
}


unordered_map<string, string> loadCommitBlobs(const string &commitHash) {
    unordered_map<string, string> blobs;
    ifstream fin(".minigit/commits/" + commitHash);
    string line;
    while (getline(fin, line)) {
        if (line.rfind("file ",0)==0) {
            string fname, blob;
            istringstream iss(line);
            iss >> fname >> fname >> blob; // skip "file"
            blobs[fname] = blob;
        }
    }
    return blobs;
}


void createBranch(const string &branchName) {
    string HEADref = getHEAD();
    string currentCommit = getCommitHash(HEADref);
    string newPath = ".minigit/refs/heads/" + branchName;
    if (fs::exists(newPath)) {
        cout << "Branch already exists!\n";
        return;
    }
    ofstream fout(newPath);
    fout << currentCommit;
    fout.close();
    cout << "Branch '" << branchName << "' created at commit: " << currentCommit << endl;
}


void checkout(const string &target) {
    string path = ".minigit/refs/heads/" + target;
    if (fs::exists(path)) {
        setHEAD(target);
        cout << "Switched to branch '" << target << "'\n";
    } else if (fs::exists(".minigit/commits/" + target)) {
        setHEAD(target); // Detached HEAD mode
        cout << "HEAD detached at commit: " << target << "\n";
    } else {
        cout << "Branch or commit not found!\n";
    }
}


string getParent(const string &commitHash) {
    ifstream fin(".minigit/commits/" + commitHash);
    string line;
    while (getline(fin, line)) {
        if (line.rfind("parent ",0)==0) {
            return line.substr(7);
        }
    }
    return "";
}

string findLCA(string a, string b) {
    set<string> ancestors;
    while (!a.empty()) {
        ancestors.insert(a);
        a = getParent(a);
    }
    while (!b.empty()) {
        if (ancestors.count(b)) return b;
        b = getParent(b);
    }
    return "";
}
string currentDateTime(){
    time_t now=time(0);
    tm*ltm = localtime(&now);
    char buf[30];
    strftime(buf,sizeof(buf), "%Y-%m-%d  %H:%M:%S", ltm);
    return string(buf);  
}


void mergeBranch(const string &otherBranch) {
    if (!fs::exists(".minigit/refs/heads/" + otherBranch)) {
        cout << "Branch not found!\n";
        return;
    }

    string currentBranch = getHEAD();
    string currentCommit = getCommitHash(currentBranch);
    string otherCommit = getCommitHash(otherBranch);
    string baseCommit = findLCA(currentCommit, otherCommit);

    unordered_map<string, string> base = loadCommitBlobs(baseCommit);
    unordered_map<string, string> head = loadCommitBlobs(currentCommit);
    unordered_map<string, string> other = loadCommitBlobs(otherCommit);
    unordered_map<string, string> result;

    set<string> allFiles;
    for (auto &[f, _] : base) allFiles.insert(f);
    for (auto &[f, _] : head) allFiles.insert(f);
    for (auto &[f, _] : other) allFiles.insert(f);

    for (const auto &file : allFiles) {
        string b = base[file];
        string h = head[file];
        string o = other[file];

        if (h == o) result[file] = h;
        else if (b == h) result[file] = o;
        else if (b == o) result[file] = h;
        else {
            cout << "CONFLICT: both modified " << file << endl;
        }
    }
    for (const auto& [file, blobHash]:result){
        if(blobHash.empty()) continue;
        ifstream bin(".minigit/objects/"+ blobHash);
        if(!bin.is_open()) continue;

        ofstream fout(file);
        fout<<bin.rdbuf();
        bin.close();
        fout.close();
    }
    string mergeMsg = "Merged branch '" + otherBranch + "' into '" + currentBranch + "'";
    string tempBlob = currentCommit + otherCommit + mergeMsg;
    string newCommitHash = to_string(hash<string>{}(tempBlob));

    ofstream commitFile(".minigit/commits/"+ newCommitHash);
    commitFile<<"hash "<<newCommitHash<<"\n";
    commitFile<<"parent "<<currentCommit<<"\n";
    commitFile<<"parent2 "<<otherCommit<<"\n";
    commitFile<<"timestamp "<<currentDateTime()<<"\n";
    commitFile<<"message "<<mergeMsg<<"\n";

    for( const auto&[file, blobHash]:result){
        commitFile<<"file "<<file<<" "<<blobHash<<"\n";
    }

    commitFile.close();
    ofstream refOut(".minigit/refs/heads/"+ currentBranch);
    refOut<<newCommitHash;
    refOut.close();
    cout<<"Merge completed and new commit created: "<<newCommitHash<<"\n";
}

