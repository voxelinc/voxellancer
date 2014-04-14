#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include <glm/glm.hpp>

#include "geometry/sphere.h"

#include "world/helper/damageimpact.h"

#include "worldtree/worldtreehint.h"


class WorldTreeHint;

/**
 * An invisible Explosion that is resolved to DamageImpact's to Voxels in range, if they are
 * not hidden behind other voxels
 */
class Shockwave {
public:
    Shockwave(const Sphere& sphere, float damage, const WorldTreeHint& worldTreeHint = WorldTreeHint());

    std::list<DamageImpact> generateDamageImpacts();


protected:
    bool isVoxelObscured(Voxel* voxel);
    DamageImpact getImpactOnVoxel(Voxel* voxel);

protected:
    Sphere m_sphere;
    float m_damage;
    WorldTreeHint m_worldTreeHint;

    std::unordered_set<Voxel*> m_potentialVoxels;
    std::unordered_map<Voxel*, std::shared_ptr<Sphere>> m_voxelSpheres;
};

