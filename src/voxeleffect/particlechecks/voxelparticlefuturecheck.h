#pragma once

class VoxelParticleData;

class VoxelParticleFutureCheck {
public:
    bool intersectsIn(const VoxelParticleData& particle, float secs);

};