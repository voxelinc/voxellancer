#pragma once

#include <memory>
#include <list>


struct VoxelParticleData;
class VoxelParticleEngine;
class VoxelParticleChecker;

/*
    Check that is guaranteed to be performed on every particle once in a
    specific interval. If check() returns true the particle is marked as dead
    and the space in the buffer may be used again for a new particle
*/
class VoxelParticleRemoveCheck {
public:
    VoxelParticleRemoveCheck(VoxelParticleEngine* world);

    void addCheck(std::shared_ptr<VoxelParticleChecker> checker);

    float interval() const;
    void setInterval(float interval);

    virtual void update(float deltaSec);


protected:
    VoxelParticleEngine* m_particleEngine;
    std::list<std::shared_ptr<VoxelParticleChecker>> m_checker;
    float m_interval;
    int m_currentIndex;

    void performChecks(int checkCount);
    void check(VoxelParticleData& particle);
};

