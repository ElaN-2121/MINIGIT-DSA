#ifndef REFERENCE_H
#define REFERENCE_H

#include <string>

class Reference {
public:
    std::string getHEAD();
    void setHEAD(const std::string& ref);

    std::string getRef(const std::string& refName);
    void setRef(const std::string& refName, const std::string& hash);
    
    
};

#endif
//
