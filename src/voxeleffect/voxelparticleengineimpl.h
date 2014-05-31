#pragma once

#include <memory>
#include <vector>
#include <stack>

#include "etc/contextdependant.h"

#include "property/property.h"

class Player;
class Camera;
struct VoxelParticleData;
class VoxelParticleSetup;
class VoxelParticleRenderer;
class VoxelParticleRemover;
class VoxelCluster;

/**
 * Main class for managing and displaying the VoxelParticles of
 * a World.
 */
class VoxelParticleEngineImpl : ContextDependant {
public:
    VoxelParticleEngineImpl();
    ~VoxelParticleEngineImpl();

    float time() const;

    int particleCount() const;
    int particleDataCount() const;
    VoxelParticleData* particleData(int index);
    std::vector<VoxelParticleData>& particleDataVector();

    void setPlayer(Player& m_player);

    void addParticle(const VoxelParticleSetup& particleSetup, const VoxelCluster* creator);
    void removeParticle(int index);

    void update(float deltaSec);
    void draw(const Camera& camera, bool transparentPass);


protected:
    float m_time;
    bool m_initialized;

    std::unique_ptr<VoxelParticleRenderer> m_renderer;
    std::unique_ptr<VoxelParticleRemover> m_remover;

    std::vector<VoxelParticleData> m_cpuParticleBuffer;
    std::stack<int> m_freeParticleBufferIndices;

    bool m_gpuParticleBufferInvalid;
    int m_gpuParticleBufferInvalidBegin;
    int m_gpuParticleBufferInvalidEnd;

    void setBufferSize(int bufferSize);
    void particleChanged(int bufferIndex);
    void updateGPUBuffers(int begin, int end);

    virtual void beforeContextDestroy();
    virtual void afterContextRebuild();
};

