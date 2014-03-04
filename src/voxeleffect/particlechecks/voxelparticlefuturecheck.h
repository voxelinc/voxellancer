#pragma once

class VoxelCluster;
struct VoxelParticleData;

class VoxelParticleFutureCheck {
public:
    static bool intersectsIn(const VoxelParticleData& particle, float futureSecs, const VoxelCluster& against);

};