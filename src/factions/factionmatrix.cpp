#include "factionmatrix.h"

#include <cassert>

#include "factionmatrix.h"
#include "factionrelation.h"
#include "playerfaction.h"
#include "piratefaction.h"
#include "policefaction.h"


FactionMatrix::FactionMatrix():
    m_playerFaction(new PlayerFaction(this)),
    m_pirateFaction(new PirateFaction(this)),
    m_policeFaction(new PoliceFaction(this))
{
    m_factions.push_back(std::unique_ptr<Faction>(m_playerFaction));
    m_factions.push_back(std::unique_ptr<Faction>(m_pirateFaction));
    m_factions.push_back(std::unique_ptr<Faction>(m_policeFaction));

    setupFactionRelations();
}

FactionMatrix::~FactionMatrix() = default;

PirateFaction* FactionMatrix::pirateFaction() {
    return m_pirateFaction;
}

PoliceFaction* FactionMatrix::policeFaction() {
    return m_policeFaction;
}

PlayerFaction* FactionMatrix::playerFaction() {
    return m_playerFaction;
}

FactionRelation& FactionMatrix::getRelationBetween(Faction* factionA, Faction* factionB) {
    FactionRelation* found = nullptr;

    for (std::unique_ptr<FactionRelation>& relation : m_relations) {
        if (relation->factionA() == factionA && relation->factionB() == factionB ||
            relation->factionB() == factionA && relation->factionA() == factionB) {
            found = relation.get();
        }
    }
    assert(found);
    return *found;
}

void FactionMatrix::setupFactionRelations() {
    m_relations.push_back(std::unique_ptr<FactionRelation>(new FactionRelation(m_playerFaction, m_pirateFaction, -20.0f)));
    m_relations.push_back(std::unique_ptr<FactionRelation>(new FactionRelation(m_playerFaction, m_policeFaction, 10.0f)));
    m_relations.push_back(std::unique_ptr<FactionRelation>(new FactionRelation(m_policeFaction, m_pirateFaction, -50.0f)));
}
