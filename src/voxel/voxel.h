#pragma once

#include <functional>

#include <glm/glm.hpp>
#include "geometry/sphere.h"

class VoxelCluster;
class WorldObject;

namespace std {
    template<> struct hash<glm::ivec3>
    {
        std::size_t operator()(const glm::ivec3 &v) const {
            return v.x ^ (v.y << 8) ^ (v.z << 16);
        }
    };
}

class Voxel
{
public:
    Voxel(const glm::ivec3& gridCell, const int color = 0xFFFFFF, float mass = 1.0f, float hp = 500.0f);
    Voxel(const Voxel& other);
    virtual ~Voxel();

    const glm::ivec3 &gridCell() const;

    virtual void addToCluster(VoxelCluster *cluster);
    virtual void addToObject(WorldObject *object);

    int color() const;

    float hp() const;
    void applyDamage(float deltaHp);

    float mass() const;

    // These hooks apply only for WorldObjects and do not need to be called by pure VoxelClusters
    virtual void onRemoval();
    virtual void onDestruction();

protected:
    glm::ivec3 m_gridCell;
    int m_color;
    float m_hp;
    float m_mass;
};

