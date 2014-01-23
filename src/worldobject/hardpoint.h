#pragma once

#include "voxel/voxelcluster.h"
#include "worldobject/weapons/weapon.h"
#include "resource/clustercache.h"

class Ship;

class Hardpoint {
public:
    Hardpoint(Ship* ship, const glm::ivec3& positionInGrid, Weapon *weapon);
    ~Hardpoint();

    void installWeapon(Weapon *weapon);
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
    Weapon* m_weapon;
};
