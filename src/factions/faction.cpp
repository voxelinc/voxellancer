#include "faction.h"

#include <cassert>

#include "factionmatrix.h"


Faction::Faction(Universe* universe, const std::string& key, const std::string& printName):
    m_universe(universe),
    m_key(key),
    m_printName(printName)
{

}

const std::string& Faction::key() const {
    return m_key;
}

void Faction::setPrintName(const std::string& printName) {
    m_printName = printName;
}

const std::string& Faction::printName() const {
    return m_printName;
}

FactionRelation& Faction::relationTo(Faction& other) {
    return m_universe->factionMatrix().getRelation(*this, other);
}

