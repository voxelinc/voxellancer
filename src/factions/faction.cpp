#include "faction.h"

Faction::Faction(FactionMatrix* factionMatrix, const std::string& key, const std::string& printName):
    m_factionMatrix(factionMatrix),
    m_key(key),
    m_printName(printName)
{

}

const std::string& Faction::key() const {
    return m_key;
}

const std::string& Faction::printName() const {
    return m_printName;
}
