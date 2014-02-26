#include "factionrelation.h"

#include "faction.h"


FactionRelation::FactionRelation(Faction* factionA, Faction* factionB, float friendliness):
    m_factionA(factionA),
    m_factionB(factionB),
    m_friendliness(friendliness)
{

}

Faction* FactionRelation::factionA() {
    return m_factionA;
}

Faction* FactionRelation::factionB() {
    return m_factionB;
}

float FactionRelation::friendliness() const {
    return m_friendliness;
}

void FactionRelation::setFriendliness(float friendliness) {
    m_friendliness = friendliness;
}

FactionRelationType FactionRelation::type() const {
    if (m_friendliness <= -30.0f) {
        return FactionRelationType::Enemy;
    }
    if (m_friendliness <= -5.0f) {
        return FactionRelationType::NegativeNeutral;
    }
    if (m_friendliness <= 5.0f) {
        return FactionRelationType::Neutral;
    }
    if (m_friendliness <= 30.0f) {
        return FactionRelationType::PositiveNeutral;
    }
    if (m_friendliness > 30.0f) {
        return FactionRelationType::Friend;
    }
}
