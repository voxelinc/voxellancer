#pragma once

#include <list>

#include "hudget.h"

#include "targetguidearrow.h"


class HUD;
class WorldObject;

class TargetGuideHudget: public Hudget {
public:
    TargetGuideHudget(HUD* hud);

    virtual glm::vec3 position() const override;
    virtual glm::quat orientation() const override;

    virtual void update(float deltaSec) override;
    virtual void draw() override;


protected:
    std::list<TargetGuideArrow> m_arrows;


    WorldObject* target();
};
