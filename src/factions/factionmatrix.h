#pragma once

#include <list>
#include <map>
#include <memory>


class Faction;
class FactionRelation;
class PlayerFaction;
class PirateFaction;
class PoliceFaction;

class FactionMatrix {
public:
    FactionMatrix();
    ~FactionMatrix();

    PirateFaction* pirateFaction();
    PoliceFaction* policeFaction();
    PlayerFaction* playerFaction();


protected:
    std::list<std::unique_ptr<Faction>> m_factions;
    std::list<std::shared_ptr<FactionRelation>> m_relations;

    PlayerFaction* m_playerFaction;
    PirateFaction* m_pirateFaction;
    PoliceFaction* m_policeFaction;

    void setupFactionRelations();
    void addFactionRelation(std::shared_ptr<FactionRelation> relation);
};

