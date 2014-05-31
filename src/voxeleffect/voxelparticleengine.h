#pragma once

#include <memory>
#include <vector>
#include <stack>

#include "etc/contextdependant.h"

#include "property/property.h"

class Player;
class Camera;
class VoxelCluster;
class VoxelParticleSetup;
class VoxelParticleEngineImpl;

/**
 * Interface abstraction for the two VoxelParticleEngineImpl's
 * for opaque and transparent particles
*/
class VoxelParticleEngine {
public:
    VoxelParticleEngine();
    ~VoxelParticleEngine();

    int particleCount() const;

    void setPlayer(Player& m_player);

    void addParticle(const VoxelParticleSetup& particleSetup, const VoxelCluster* creator);

    void update(float deltaSec);
    void draw(const Camera& camera, bool transparentPass);


protected:

    std::unique_ptr<VoxelParticleEngineImpl> m_opaqueEngine;
    std::unique_ptr<VoxelParticleEngineImpl> m_transparentEngine;

};

