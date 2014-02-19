#pragma once

#include <memory>
#include <vector>
#include <stack>
#include <list>

#include "glow/ref_ptr.h"
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include "camera/camera.h"

#include "property/property.h"

#include "voxelparticledata.h"
#include "voxelparticlesetup.h"
#include "voxelparticlerenderer.h"
#include "voxelparticleexpirecheck.h"
#include "voxelparticleintersectioncheck.h"


/*
    Main class for managing and displaying the VoxelParticles of
    a World.
*/
class VoxelParticleEngine {
public:
    VoxelParticleEngine();

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

    VoxelParticleRenderer m_renderer;
    VoxelParticleExpireCheck m_expireCheck;
    VoxelParticleIntersectionCheck m_intersectionCheck;

    std::vector<VoxelParticleData> m_cpuParticleBuffer;
    std::stack<int> m_freeParticleBufferIndices;


    bool m_gpuParticleBufferInvalid;
    int m_gpuParticleBufferInvalidBegin;
    int m_gpuParticleBufferInvalidEnd;

    void setBufferSize(int bufferSize);
    void particleChanged(int bufferIndex);
    void updateGPUBuffers(int begin, int end);
};

