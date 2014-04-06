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

    float compensate(float damage);

    virtual float maxHP() const = 0;

    virtual float regeneration() const = 0;

    virtual void update(float deltaSec);


protected:
    float m_hp;
    ShieldSlot* m_shieldSlot;

    virtual void onDamageTaken(float damage);
};

