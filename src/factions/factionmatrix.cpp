#include "factionmatrix.h

#include "playerfaction.h"
#include "piratefaction.h"
#include "policefaction.h"


FactionMatrix::FactionMatrix()
{
    setupFactions();
}

FactionMatrix::~FactionMatrix() = default;

FactionRelation& FactionMatrix::getRelationBetween(Faction* factionA, Faction* factionB) {
    for(std::unique_ptr<FactionRelation>& relation : m_relations) {
        if (relation->factionA() == factionA && relation->factionB() == factionB ||
            relation->factionB() == factionA && relation->factionA() == factionB)
        {
            return *relation.get();
        }
    }
    assert(0);
}

void FactionMatrix::setupFactions() {
    PlayerFaction* playerFaction = new PlayerFaction(this);
    PirateFaction* pirateFaction = new PirateFaction(this);
    PoliceFaction* policeFaction = new PoliceFaction(this);

    FactionRelation* playerPiratesRelation(playerFaction, pirateFaction, -20.0f);
    FactionRelation* playerPoliceRelation(playerFaction, policeFaction, 10.0f);
    FactionRelation* piratePoliceRelation(policeFaction, pirateFaction, -50.0f);

    m_factions.push_back(playerfaction);
    m_factions.push_back(pirateFaction);
    m_factions.push_back(policeFaction);

    m_relations.push_back(playerPiratesRelation);
    m_relations.push_back(playerPoliceRelation);
    m_relations.push_back(piratePoliceRelation);
}
