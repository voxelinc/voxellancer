#pragma once

#include <list>


#include "world/helper/damageimpact.h"
#include "world/helper/voxelaccumulator.h"


class DamageForwarder
{
public:
    void forwardDamageImpacts(std::list<DamageImpact> &dampedDeadlyDamageImpacts);
    void dontForwardTo(std::list<Voxel*> &deadVoxels);

    std::list<DamageImpact> forwardedDamageImpacts();


protected:;
    WorldObject* m_currentWorldObject;
    Voxel* m_currentDeadVoxel;
    glm::vec3 m_currentDamageVec;
    float m_currentFieldOfDamage;

    VoxelAccumulator<DamageImpact> m_damageImpactAccumulator;


    void forward(DamageImpact& damageImpact);
    float forwardFactor(float dotProduct, float fieldOfDamage);
    glm::vec3 calculateForwardingToVoxel(Voxel* voxel);
};

