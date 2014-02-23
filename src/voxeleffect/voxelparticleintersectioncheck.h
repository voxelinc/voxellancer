#pragma once

#include "property/property.h"

#include "voxelparticlechecker.h"

class VoxelParticleEngine;
struct VoxelParticleData;


/*
    Regular check that removes particles that intersect with WorldObjects
*/
class VoxelParticleIntersectionCheck: public VoxelParticleChecker {
public:
    VoxelParticleIntersectionCheck(VoxelParticleEngine* engine);

    virtual bool isDead(const VoxelParticleData& particle) override;

protected:
    VoxelParticleEngine* m_particleEngine;

};

