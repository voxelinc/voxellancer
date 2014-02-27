#include "factionrelation.h"

#include <cassert>

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
    return FactionRelationType::Friend;
}

std::string FactionRelation::typeName(FactionRelationType type) {
    switch (type) {
        case FactionRelationType::Enemy: return "Enemy";
        case FactionRelationType::NegativeNeutral: return "Rather Negative";
        case FactionRelationType::Neutral: return "Neutral";
        case FactionRelationType::PositiveNeutral: return "Rather Positive";
        case FactionRelationType::Friend: return "Friend";
        default: assert(0);
    }
    return "";
}

