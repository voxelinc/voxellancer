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

void FactionMatrix::setupFactionRelations() {
    addFactionRelation(std::make_shared<FactionRelation>(m_playerFaction, m_pirateFaction, -80.0f));
    addFactionRelation(std::make_shared<FactionRelation>(m_playerFaction, m_policeFaction, 10.0f));
    addFactionRelation(std::make_shared<FactionRelation>(m_policeFaction, m_pirateFaction, -50.0f));
}

void FactionMatrix::addFactionRelation(std::shared_ptr<FactionRelation> relation) {
    relation->factionA()->setRelation(relation);
    relation->factionB()->setRelation(relation);
}

