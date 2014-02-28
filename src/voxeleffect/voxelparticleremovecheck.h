#pragma once


struct VoxelParticleData;
class VoxelParticleEngine;

/*
    Check that is guaranteed to be performed on every particle once in a
    specific interval. If check() returns true the particle is marked as dead
    and the space in the buffer may be used again for a new particle
*/
class VoxelParticleRemoveCheck {
public:
    VoxelParticleRemoveCheck(VoxelParticleEngine* engine);

    float interval() const;
    void setInterval(float interval);

    virtual void update(float deltaSec);


protected:
    VoxelParticleEngine* m_engine;
    float m_interval;
    int m_currentIndex;


    void performChecksParallel(int checkCount);
    void performChecksSequential(int checkCount);

    virtual bool check(VoxelParticleData* particle) = 0;
    virtual bool isParallel(int checkCount) = 0;
};

