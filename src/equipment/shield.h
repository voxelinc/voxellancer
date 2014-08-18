#pragma once

#include "equipment.h"


class ShieldSlot;

class Shield : public Equipment {
public:
    Shield(const std::string& key);
    virtual ~Shield();

    ShieldSlot* shieldSlot();
    void setShieldSlot(ShieldSlot* shieldSlot);

    float hp() const;
    void setHP(float hp);

    float maxHP() const;
    void setMaxHP(float maxHP);

    float regeneration() const;
    void setRegeneration(float regeneration);

    float compensate(float damage);

    virtual void update(float deltaSec);


protected:
    float m_hp;
    float m_regeneration;
    float m_maxHP;
    ShieldSlot* m_shieldSlot;

    virtual void onDamageTaken(float damage);
};

