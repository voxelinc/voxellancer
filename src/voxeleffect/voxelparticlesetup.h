#pragma once

#include "geometry/acceleration.h"
#include "geometry/speed.h"
#include "geometry/transform.h"

#include "display/rendering/visuals.h"

#include "voxelparticledata.h"


/**
 *  Setup for a particle used for its spawning by the VoxelParticlewWorld.
 *  Note that the VoxelParticlewWorld itsself stores the Particle optimized
 *  inside a buffer of VoxelParticleData, which is a data-only-structure
*/
class VoxelParticleSetup {
public:
    VoxelParticleSetup(const Transform& transform, const Visuals& visuals, const Speed& speed, float lifetime);

    VoxelParticleData toData(float timeSecs) const;

    Visuals visuals() const;


protected:
    Transform m_transform;
    Visuals m_visuals;
    Speed m_speed;
    float m_lifetime;
};
