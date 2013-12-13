#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include <glow/Texture.h>
#include <glow/ref_ptr.h>

#include "geometry/aabb.h"

#include "property/property.h"

class VoxelExplosionGenerator
{
public:
    VoxelExplosionGenerator();
    virtual ~VoxelExplosionGenerator();

    void spawnVoxelExplosion(const glm::vec3& position, int color = 0xFFFFFF, float spawnRadius = 1.0f, float force = 1.0f, const glm::vec3& impactVector = glm::vec3(0));

protected:
    Property<int> prop_spawnCount;

};

