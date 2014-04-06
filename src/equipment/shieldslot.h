#pragma once

#include <memory>

#include "worldobjectslot.h"


class Shield;

class ShieldSlot : public WorldObjectSlot {
public:
    ShieldSlot(WorldObjectComponents* components);

    std::shared_ptr<Shield>& shield();
    void setShield(const std::shared_ptr<Shield>& shield);

    void update(float deltaSec);


protected:
    std::shared_ptr<Shield> m_shield;
};
