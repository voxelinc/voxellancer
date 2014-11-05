#pragma once
#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <utility>

#include "utils/pairhash.h"

class Faction;
class FactionRelation;


class FactionMatrix {
public:
    FactionMatrix();
    ~FactionMatrix();

    Faction& pirateFaction();
    Faction& policeFaction();
    Faction& playerFaction();
    Faction& unknownFaction();

    Faction& getFaction(const std::string& factionName);
    void addFaction(std::shared_ptr<Faction> faction);

    FactionRelation& getRelation(Faction& factionA, Faction& factionB);
    FactionRelation& getRelationToPlayer(Faction& faction);

    void changeFriendlinessToPlayer(Faction& faction, float difference);
    void changeFriendlinessToFaction(Faction& faction, Faction& otherFaction, float difference);

protected:
    std::unordered_map<std::string, std::shared_ptr<Faction>> m_factions;
    std::unordered_map<std::pair<Faction*, Faction*>, std::shared_ptr<FactionRelation>> m_relations;

    void setupRelations();
    std::pair<Faction*, Faction*> uniquePair(Faction& factionA, Faction& factionB);
};

