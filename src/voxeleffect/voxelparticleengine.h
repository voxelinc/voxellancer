#pragma once

#include <memory>
#include <vector>
#include <stack>

#include <glow/ref_ptr.h>

#include "property/property.h"

class Camera;
struct VoxelParticleData;
class VoxelParticleSetup;
class VoxelParticleRenderer;
class VoxelParticleRemoveCheck;

/*
    Main class for managing and displaying the VoxelParticles of
    a World.
*/
class VoxelParticleEngine {
public:
    VoxelParticleEngine();
    ~VoxelParticleEngine();

    float time() const;

    int particleDataCount() const;
    VoxelParticleData* particleData(int index);

    void addParticle(const VoxelParticleSetup& particleSetup);
    void removeParticle(int index);

    void update(float deltaSec);
    void draw(Camera& camera);


protected:
    float m_time;
    bool m_initialized;

    std::unique_ptr<VoxelParticleRenderer> m_renderer;
    std::unique_ptr<VoxelParticleRemoveCheck> m_removeCheck;

    std::vector<VoxelParticleData> m_cpuParticleBuffer;
    std::stack<int> m_freeParticleBufferIndices;

    bool m_gpuParticleBufferInvalid;
    int m_gpuParticleBufferInvalidBegin;
    int m_gpuParticleBufferInvalidEnd;

    void setBufferSize(int bufferSize);
    void particleChanged(int bufferIndex);
    void updateGPUBuffers(int begin, int end);
};

