#pragma once

#include <string>


class Faction;

enum class FactionRelationType {
    Enemy = 0,
    NegativeNeutral,
    Neutral,
    PositiveNeutral,
    Friend
};

class FactionRelation {
public:
    FactionRelation(Faction* factionA, Faction* factionB, float friendliness);

    Faction* factionA();
    Faction* factionB();

    float friendliness() const;
    void setFriendliness(float friendliness);

    FactionRelationType type() const;

    static std::string typeName(FactionRelationType type);


protected:
    Faction* m_factionA;
    Faction* m_factionB;
    float m_friendliness;
    FactionRelationType m_type;
};

