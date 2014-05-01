#pragma once

#include <memory>
#include <list>

#include "property/property.h"


template<typename T>
class ThreadPool;

class Player;
struct VoxelParticleData;
class VoxelParticleEngineImpl;
class VoxelParticleRemoveCheck;

/*
    Check that is guaranteed to be performed on every particle once in a
    specific interval. If check() returns true the particle is marked as dead
    and the space in the buffer may be used again for a new particle
*/
class VoxelParticleRemover {
public:
    VoxelParticleRemover(VoxelParticleEngineImpl* world);
    ~VoxelParticleRemover();

    void addCheck(std::shared_ptr<VoxelParticleRemoveCheck> checker);

    void setPlayer(Player& player);

    float interval() const;
    void setInterval(float interval);

    virtual void update(float deltaSec);


protected:
    VoxelParticleEngineImpl* m_particleEngine;
    std::vector<std::shared_ptr<VoxelParticleRemoveCheck>> m_checker;
    std::unique_ptr<ThreadPool<VoxelParticleData>> m_threadPool;
    
    Property<float> m_interval;
    Property<bool> m_multithreaded;
    
    int m_currentIndex;

    void performChecks(int checkCount);
    bool isDead(VoxelParticleData& particle);
    void beforeCheck();
};

