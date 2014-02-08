#pragma once


class VoxelParticleData;
class VoxelParticleWorld;

/*
    Check that is guaranteed to be performed on every particle once in a
    specific interval. If check() returns true the particle is marked as dead
    and the space in the buffer may be used again for a new particle
*/
class VoxelParticleRemoveCheck {
public:
    VoxelParticleRemoveCheck(VoxelParticleWorld* world);

    float interval() const;
    void setInterval(float interval);

    virtual void update(float deltaSec);


protected:
    VoxelParticleWorld* m_world;
    float m_interval;
    int m_currentIndex;


    virtual bool check(VoxelParticleData* particle) = 0;
};

