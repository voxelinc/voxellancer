#pragma once

#include "voxel/voxelcluster.h"
#include "worldobject/weapons/weapon.h"
#include "resource/clustercache.h"

class Ship;

class Hardpoint {
public:
    Hardpoint(Ship* ship, const glm::vec3& positionInGrid, Weapon *weapon);
    ~Hardpoint();
    void setWeapon(Weapon *weapon);

    Weapon* weapon();
    glm::vec3 position(); // in world coordinates
    Ship* ship();

    void update(float delta_sec);
    AimType aimType();
    void shootAtPoint(glm::vec3 target);
    void shootAtObject(WorldObject* target);
    float aimRange();

    void voxelRemoved();

private:
    Ship* m_ship;
    glm::vec3 m_positionInGrid;
    Weapon* m_weapon;
};