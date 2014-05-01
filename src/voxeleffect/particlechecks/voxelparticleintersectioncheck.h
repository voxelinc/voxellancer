#pragma once

#include "property/property.h"

#include "voxelparticleremovecheck.h"

#include "geometry/sphere.h"

class Player;
class VoxelParticleEngineImpl;
struct VoxelParticleData;


/*
    Regular check that removes particles that intersect with WorldObjects
*/
class VoxelParticleIntersectionCheck: public VoxelParticleRemoveCheck {
public:
    VoxelParticleIntersectionCheck(const VoxelParticleEngineImpl& engine);

    virtual bool isDead(const VoxelParticleData& particle) override;

protected:
    const VoxelParticleEngineImpl& m_particleEngine;
    Sphere m_Sphere;

    virtual void beforeCheck();

};

