#pragma once

#include <glm/glm.hpp>


class Voxel;
class WorldObject;

class Impulse
{
public:
    Impulse(WorldObject* worldObject, Voxel* voxel, const glm::vec3& speed, float mass, const glm::vec3& normal);

    WorldObject* worldObject();
    const WorldObject* worldObject() const;

    Voxel* voxel();
    const Voxel* voxel() const;

    const glm::vec3& speed() const;

    float mass() const;

    const glm::vec3& normal() const;


    void add(const Impulse& impulse);


protected:
    WorldObject* m_worldObject;
    Voxel* m_voxel;
    glm::vec3 m_speed;
    float m_mass;
    glm::vec3 m_normal;
};

