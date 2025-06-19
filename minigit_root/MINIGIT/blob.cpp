// blob.cpp
#include "blob.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <direct.h>  

#else
#include <sys/stat.h>
  
#endif

using namespace std;


string simpleHash(const string& data) {
	
    unsigned long hash = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        char c = data[i];
        hash = (hash * 101 + c) % 1000000007;  
    }
    stringstream ss;
    ss << hex << hash;
    return ss.str();
    
}

// Constructor
Blob::Blob(const string& filename) : filename(filename) {
    ifstream file(filename.c_str());  
    if (file) {
        ostringstream ss;
        ss << file.rdbuf();
        content = ss.str();
        hash = simpleHash(content);
    } else {
        cerr << "Failed to open file: " << filename << endl;
    }
}


void Blob::save() {
#ifdef _WIN32
    _mkdir(".minigit");
    _mkdir(".minigit\\objects");
#else
    mkdir(".minigit", 0777);
    mkdir(".minigit/objects", 0777);
#endif

    string path = ".minigit/objects/" + hash;
    ofstream out(path.c_str(), ios::binary);  
    if (out) {
    	
        out << content;
        out.close();
        cout << "Blob saved with hash: " << hash << endl;
    } else {
        cerr << "Failed to save blob file." << endl;
        
    }
}
//
