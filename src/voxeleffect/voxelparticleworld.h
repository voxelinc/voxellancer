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



class VoxelParticleWorld {
public:
    VoxelParticleWorld();

    float time() const;

    void addParticle(const VoxelParticleSetup& particleSetup);

    void update(float deltaSec);
    void draw(Camera& camera);


protected:
    float m_time;
    bool m_initialized;

    VoxelParticleRenderer m_renderer;

    std::vector<VoxelParticleData> m_cpuParticleBuffer;
    std::stack<int> m_freeParticleBufferIndices;

    Property<float> m_fullDeadCheckInterval;
    int m_deadCheckIndex;

    Property<float> m_fullIntersectionCheckInterval;
    int m_intersectionCheckIndex;


    bool m_gpuParticleBufferInvalid;
    int m_gpuParticleBufferInvalidBegin;
    int m_gpuParticleBufferInvalidEnd;

    void setBufferSize(int bufferSize);
    void setParticleAt(const VoxelParticleData& particle, int bufferIndex);
    void updateGPUBuffers();

    void performDeadChecks(float deltaSec);
    void performIntersectionChecks(float deltaSec);

    bool intersects(VoxelParticleData* particle);

    void initialize();
};

