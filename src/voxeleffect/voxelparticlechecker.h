#pragma once

struct VoxelParticleData;

class VoxelParticleChecker {
public:
    virtual bool isDead(const VoxelParticleData& particle) = 0;
};