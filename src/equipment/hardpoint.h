#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "worldobjectslot.h"


class Weapon;
class HardpointVoxel;
class WorldObjectComponents;

/*
    Slot into which interchangeable weapons may be mounted
    direction and fieldOfAim form a cone in which the hardpoint can fire its weapons
*/
class Hardpoint: public WorldObjectSlot {
public:
    Hardpoint(WorldObjectComponents* components, HardpointVoxel* voxel);

    HardpointVoxel* voxel();

    const std::shared_ptr<Weapon>& weapon();
    void setWeapon(const std::shared_ptr<Weapon>& weapon);

    const glm::vec3& direction() const;
    void setDirection(const glm::vec3& direction);

    float fieldOfAim() const;
    void setFieldOfAim(float fieldOfAim);

    bool inFieldOfAim(const glm::vec3& point);

    void update(float deltaSec);

    void onVoxelRemoval();


protected:
    HardpointVoxel* m_voxel;
    std::shared_ptr<Weapon> m_weapon;

    glm::vec3 m_direction;
    float m_fieldOfAim;
};

