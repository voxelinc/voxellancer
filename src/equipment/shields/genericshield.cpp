#include "genericshield.h"


GenericShield::GenericShield(const std::string& equipmentKey):
    Shield(equipmentKey),
    m_regeneration(0.0f),
    m_maxHP(0.0f)
{

}

float GenericShield::regeneration() const {
    return m_regeneration;
}

void GenericShield::setRegeneration(float regeneration) {
    m_regeneration = regeneration;
}

float GenericShield::maxHP() const {
    return m_maxHP;
}

void GenericShield::setMaxHP(float maxHP) {
    m_maxHP = maxHP;
}

