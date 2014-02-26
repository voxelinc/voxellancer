#pragma once

#include <string>


class FactionMatrix;

class Faction {
public:
    Faction(FactionMatrix* factionMatrix, const std::string& key, const std::string& printName);

    const std::string& key() const;
    const std::string& printName() const;


protected:
    FactionMatrix* m_factionMatrix;
    std::string m_key;
    std::string m_printName;
};

