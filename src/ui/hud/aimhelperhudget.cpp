#include "aimhelperhudget.h"

#include "worldobject/ship.h"
#include "worldobject/hardpoint.h"
#include "worldobject/weapons/weapon.h"

#include "player.h"

#include "hud.h"


AimHelperHudget::AimHelperHudget(HUD* hud):
    Hudget(hud),
    m_voxels(this)
{
}

void AimHelperHudget::update(float deltaSec) {
    Ship* playerShip = m_hud->player()->playerShip();
    WorldObject* target = playerShip->targetObject();
    float bulletSpeed = this->bulletSpeed();


}

void AimHelperHudget::draw() {

}

float AimHelperHudget::bulletSpeed() {
    return m_hud->player()->playerShip()->hardpoints().front()->weapon()->bulletSpeed();
}

