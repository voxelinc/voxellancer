#pragma once

#include "equipment/shield.h"


class GenericShield : public Shield {
public:
    GenericShield(const std::string& equipmentKey);

    float regeneration() const override;
    void setRegeneration(float regeneration);

    float maxHP() const override;
    void setMaxHP(float maxHP);


protected:
    float m_regeneration;
    float m_maxHP;
};
