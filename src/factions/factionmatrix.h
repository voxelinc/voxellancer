#pragma once

#include <list>
#include <memory>


class Faction;

class FactionMatrix {
public:
    FactionMatrix();
    ~FactionMatrix();

    FactionRelation* getRelationBetween(Faction* factionA, Faction* factionB);


protected:
    std::list<std::unique_ptr<Faction>> m_factions;
    std::list<std::unique_ptr<FactionRelation>> m_relations;


    void setupFactions();
};

