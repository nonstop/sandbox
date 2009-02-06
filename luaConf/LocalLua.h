#ifndef LOCALLUA_H
#define LOCALLUA_H

#include <string>

class LocalLua
{
public:
    LocalLua();
    virtual ~LocalLua();

    void process(const std::string& configFile);
    void readVar(const std::string& name);
    const std::string& getVar(const std::string& name, const std::string& defaultValue = "") const;
};

#endif /* LOCALLUA_H */

