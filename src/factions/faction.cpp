#include "faction.h"

#include <cassert>

#include "universe/universe.h"

#include "factionmatrix.h"


Faction::Faction(FactionMatrix& matrix, const std::string& key, const std::string& printName):
    m_matrix(matrix),
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
    return m_matrix.getRelation(*this, other);
}

