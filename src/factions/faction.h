#pragma once

#include <map>
#include <memory>
#include <string>


class FactionRelation;

class Faction {
public:
    Faction(const std::string& key, const std::string& printName);

    const std::string& key() const;
    void setPrintName(const std::string& printName);
    const std::string& printName() const;
    
    FactionRelation& relationTo(Faction& other);

protected:
    std::string m_key;
    std::string m_printName;
};

