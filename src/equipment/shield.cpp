#include "shield.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "shieldslot.h"


Shield::Shield(const std::string& key):
    Equipment(key),
    m_hp(0.0f),
    m_shieldSlot(nullptr)
{

}

Shield::~Shield() = default;

ShieldSlot* Shield::shieldSlot() {
    return m_shieldSlot;
}

void Shield::setShieldSlot(ShieldSlot* shieldSlot) {
    m_shieldSlot = shieldSlot;
}

float Shield::hp() const {
    return m_hp;
}

void Shield::setHP(float hp) {
    assert(hp <= maxHP() && hp >= 0);
    m_hp = hp;
}

float Shield::compensate(float damage) {
    float compensatedDamage = std::min(m_hp, damage);
    float forwardedDamage = damage - compensatedDamage;

    m_hp -= compensatedDamage;
    onDamageTaken(compensatedDamage);

    return forwardedDamage;
}

void Shield::update(float deltaSec) {
    std::cout << m_hp << " " << regeneration() << " " << maxHP() << " " << deltaSec << std::endl;
    m_hp += regeneration() * deltaSec;
    m_hp = std::min(m_hp, maxHP());
}

void Shield::onDamageTaken(float damage) {

}

