#include "aimhelperhudget.h"

#include "utils/tostring.h"

#include "worldobject/ship.h"
#include "worldobject/hardpoint.h"
#include "worldobject/helper/hardpointaimhelper.h"
#include "worldobject/weapons/weapon.h"

#include "player.h"

#include "hud.h"


AimHelperHudget::AimHelperHudget(HUD* hud):
    Hudget(hud),
    m_voxels(this)
{
}

glm::vec3 AimHelperHudget::position() const {
    return m_position;
}

glm::quat AimHelperHudget::orientation() const {
    return m_hud->orientation();
}

void AimHelperHudget::update(float deltaSec) {
    Ship* ship = m_hud->player()->playerShip();
    WorldObject* targetObject = ship->targetObject();

    if(targetObject) {
        if(!ship->hardpoints().empty()) {
            m_position = glm::vec3(0.0f, 0.0f, 0.0f);

            for(Hardpoint* hardpoint : ship->hardpoints()) {
                HardpointAimHelper aimHelper(hardpoint, targetObject);
                aimHelper.aim();
                m_position += aimHelper.point();
            }
            m_position /= ship->hardpoints().size();
            //std::cout << "Position: " << toString(m_position) << " " << toString(targetObject->transform().position()) << std::endl;
        }
    }
}

void AimHelperHudget::draw() {
    m_voxels.draw();
}

