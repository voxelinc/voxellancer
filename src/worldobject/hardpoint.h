#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "weapons/weapon.h"

class Ship;
class Weapon;

class Hardpoint {
public:
    Hardpoint(Ship* ship, const glm::ivec3& positionInGrid, std::shared_ptr<Weapon> weapon);
    ~Hardpoint();

    void installWeapon(std::shared_ptr<Weapon> weapon);
    Weapon* weapon();

    glm::vec3 position(); // in world coordinates
    Ship* ship();

    void update(float deltaSec);
    AimType aimType();
    void shootAtPoint(glm::vec3 target);
    void shootAtObject(WorldObject* target);
    float range();

    void voxelRemoved();

private:
    Ship* m_ship;
    glm::vec3 m_positionInGrid;
    std::shared_ptr<Weapon> m_weapon;
};
