#include "faction.h"

#include <cassert>


Faction::Faction(const std::string& key, const std::string& printName):
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
