#include "faction.h"

#include <cassert>

#include "factionrelation.h"


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

std::shared_ptr<FactionRelation>& Faction::relationTo(Faction* faction) {
    decltype(m_relations)::iterator i = m_relations.find(faction);
    assert(i != m_relations.end());
    return i->second;
}

void Faction::setRelation(std::shared_ptr<FactionRelation>& relation) {
    assert(relation->factionA() == this || relation->factionB() == this);
    Faction* other = relation->factionA() == this ? relation->factionB() : relation->factionA();
    m_relations.insert(std::make_pair(other, relation));
}

