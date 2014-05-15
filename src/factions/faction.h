#pragma once

#include <map>
#include <memory>
#include <string>


class FactionRelation;
class Universe;

class Faction {
public:
    Faction(Universe* universe, const std::string& key, const std::string& printName);

    const std::string& key() const;
    void setPrintName(const std::string& printName);
    const std::string& printName() const;

    FactionRelation& relationTo(Faction& other);

protected:
    Universe* m_universe;
    std::string m_key;
    std::string m_printName;
};

