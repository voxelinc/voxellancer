#pragma once

#include <memory>

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

    const std::shared_ptr<Weapon>& weapon();
    void setWeapon(const std::shared_ptr<Weapon>& weapon);

    const glm::vec3& direction() const;
    void setDirection(const glm::vec3& direction);

    const glm::vec2& fieldOfAim() const;
    void setFieldOfAim(const glm::vec2& fieldOfAim);

    void update(float deltaSec);

protected:
    HardpointVoxel* m_voxel;
    std::shared_ptr<Weapon> m_weapon;

    glm::vec3 m_direction;
    glm::vec2 m_fieldOfAim;
};

