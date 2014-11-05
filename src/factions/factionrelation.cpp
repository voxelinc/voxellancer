#include "factionrelation.h"

#include <cassert>

#include "faction.h"
#include "glm/glm.hpp"


FactionRelation::FactionRelation(Faction& factionA, Faction& factionB, float friendliness):
    m_factionA(factionA),
    m_factionB(factionB),
    m_friendliness(friendliness)
{
}

Faction& FactionRelation::factionA() {
    return m_factionA;
}

Faction& FactionRelation::factionB() {
    return m_factionB;
}

float FactionRelation::friendliness() const {
    return m_friendliness;
}

void FactionRelation::setFriendliness(float friendliness) {
    m_friendliness = friendliness;
}

bool FactionRelation::isHostile() const {
    return type() == FactionRelationType::Enemy;
}

bool FactionRelation::isFriendly() const {
    return type() == FactionRelationType::Friend;
}

FactionRelationType FactionRelation::type() const {
    return type(m_friendliness);
}

void FactionRelation::changeFriendliness(float difference) {
    m_friendliness = glm::max(-100.0f, glm::min(100.0f, m_friendliness + difference));
}

FactionRelationType FactionRelation::type(float friendliness) {
    if (friendliness <= -30.0f) {
        return FactionRelationType::Enemy;
    }
    if (friendliness <= -5.0f) {
        return FactionRelationType::NegativeNeutral;
    }
    if (friendliness <= 5.0f) {
        return FactionRelationType::Neutral;
    }
    if (friendliness <= 30.0f) {
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

