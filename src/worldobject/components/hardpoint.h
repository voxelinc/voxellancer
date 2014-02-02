#pragma once

#include <glm/glm.hpp>

#include "worldobjectslot.h"


class Weapon;
class HardpointVoxel;
class WorldObjectComponents;

/*
    Slot into which interchangeable weapons may be mounted
*/
class Hardpoint: public WorldObjectSlot {
public:
    Hardpoint(WorldObjectComponents* components, HardpointVoxel* voxel);

    HardpointVoxel* voxel();

    Weapon* weapon();
    void setWeapon(Weapon* weapon);

    const glm::vec3& direction() const;
    void setDirection(const glm::vec3& direction);

    const glm::vec2& fieldOfAim() const;
    void setFieldOfAim(const glm::vec2& fieldOfAim);

    void update(float deltaSec);

    void onVoxelRemoval();


protected:
    HardpointVoxel* m_voxel;
    Weapon* m_weapon;

    glm::vec3 m_direction;
    glm::vec2 m_fieldOfAim;
};

