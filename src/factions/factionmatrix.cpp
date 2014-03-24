#include "factionmatrix.h"

#include <cassert>

#include <glow/logging.h>

#include "factionmatrix.h"
#include "factionrelation.h"
#include "faction.h"


FactionMatrix::FactionMatrix():
    m_factions()
{
    // create default factions
    addFaction(std::make_shared<Faction>("player", "Player"));
    addFaction(std::make_shared<Faction>("pirate", "Pirate"));
    addFaction(std::make_shared<Faction>("police", "Police"));
    addFaction(std::make_shared<Faction>("unknown", "Unknown"));

    setupRelations();
}

FactionMatrix::~FactionMatrix() = default;

Faction& FactionMatrix::pirateFaction() {
    return getFaction("pirate");
}

Faction& FactionMatrix::policeFaction() {
    return getFaction("police");
}

Faction& FactionMatrix::playerFaction() {
    return getFaction("player");
}

Faction& FactionMatrix::unknownFaction() {
    return getFaction("unknown");
}

Faction& FactionMatrix::getFaction(const std::string& factionName) {
    auto iter = m_factions.find(factionName);
    if (iter == m_factions.end()) {
        glow::warning("FactionMatrix: created non existing faction %;", factionName);
        addFaction(std::make_shared<Faction>(factionName, factionName));
        return getFaction(factionName);
    }
    return *iter->second;
}

void FactionMatrix::addFaction(std::shared_ptr<Faction> faction) {
    assert(m_factions.find(faction->key()) == m_factions.end());
    m_factions[faction->key()] = faction;
    getRelation(*faction, *faction).setFriendliness(100);
}

FactionRelation& FactionMatrix::getRelation(Faction& factionA, Faction& factionB) {
    auto iter = m_relations.find(uniquePair(factionA, factionB));
    if (iter == m_relations.end()) {
        auto relation = std::make_shared<FactionRelation>(factionA, factionB, 0.0f);
        m_relations[uniquePair(factionA, factionB)] = relation;
        return *relation;
    }
    return *iter->second;
}

FactionRelation& FactionMatrix::getRelationToPlayer(Faction& faction) {
    return getRelation(faction, playerFaction());
}

void FactionMatrix::setupRelations() {
    getRelation(playerFaction(), pirateFaction()).setFriendliness(-20.0f);
    getRelation(playerFaction(), policeFaction()).setFriendliness(10.0f);
    getRelation(policeFaction(), pirateFaction()).setFriendliness(-50.0f);
}

std::pair<Faction*, Faction*> FactionMatrix::uniquePair(Faction& factionA, Faction& factionB) {
    if (factionA.key() < factionB.key()) {
        return std::pair<Faction*, Faction*>(&factionA, &factionB);
    } else {
        return std::pair<Faction*, Faction*>(&factionB, &factionA);
    }
}

