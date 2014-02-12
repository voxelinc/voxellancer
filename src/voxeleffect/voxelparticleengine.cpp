#include "voxelparticleengine.h"

#include <omp.h>
#include <iostream>
#include <vector>
#include <string>

#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/global.h>

#include "geometry/point.h"

#include "utils/math.h"

#include "voxel/voxelrenderer.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"

#include "voxelparticledata.h"
#include "voxelmesh.h"


VoxelParticleEngine::VoxelParticleEngine():
    m_time(0.0f),
    m_initialized(false),
    m_renderer(this),
    m_expireCheck(this),
    m_intersectionCheck(this),
    m_gpuParticleBufferInvalid(false),
    m_gpuParticleBufferInvalidBegin(0),
    m_gpuParticleBufferInvalidEnd(0)
{
    setBufferSize(1024);
}

float VoxelParticleEngine::time() const {
    return m_time;
}

int VoxelParticleEngine::particleDataCount() const {
    return m_cpuParticleBuffer.size();
}

VoxelParticleData* VoxelParticleEngine::particleData(int index) {
    assert(index < m_cpuParticleBuffer.size());
    return &m_cpuParticleBuffer[index];
}

void VoxelParticleEngine::addParticle(const VoxelParticleSetup& particleSetup) {
    if(m_freeParticleBufferIndices.empty()) {
        setBufferSize(m_cpuParticleBuffer.size() * 2);
    }

    int bufferIndex = m_freeParticleBufferIndices.top();
    setParticleAt(particleSetup.toData(m_time), bufferIndex);
    m_freeParticleBufferIndices.pop();
}

void VoxelParticleEngine::removeParticle(int index) {
    assert(index < m_cpuParticleBuffer.size());

    VoxelParticleData& particle = m_cpuParticleBuffer[index];
    particle.dead = true;
    m_freeParticleBufferIndices.push(index);
}

void VoxelParticleEngine::update(float deltaSec) {
    m_time += deltaSec;

    m_expireCheck.update(deltaSec);
    m_intersectionCheck.update(deltaSec);
}

void VoxelParticleEngine::draw(Camera& camera) {
    if (m_gpuParticleBufferInvalid) {
        updateGPUBuffers();
    }

    m_renderer.draw(camera);
}

void VoxelParticleEngine::setParticleAt(const VoxelParticleData& particle, int bufferIndex) {
    m_cpuParticleBuffer[bufferIndex] = particle;

    if(m_gpuParticleBufferInvalid) {
        if(bufferIndex < m_gpuParticleBufferInvalidBegin) {
            m_gpuParticleBufferInvalidBegin = bufferIndex;
        } else if (bufferIndex > m_gpuParticleBufferInvalidEnd) {
            m_gpuParticleBufferInvalidEnd = bufferIndex;
        }

    } else {
        m_gpuParticleBufferInvalid = true;
        m_gpuParticleBufferInvalidBegin = bufferIndex;
        m_gpuParticleBufferInvalidEnd = bufferIndex;
    }
}

void VoxelParticleEngine::setBufferSize(int bufferSize) {
    for(int i = m_cpuParticleBuffer.size(); i < bufferSize; i++) {
        m_freeParticleBufferIndices.push(i);
    }

    m_cpuParticleBuffer.resize(bufferSize);

    // Rather be safe than sorry for now
    m_gpuParticleBufferInvalid = true;
    m_gpuParticleBufferInvalidBegin = 0;
    m_gpuParticleBufferInvalidEnd = bufferSize - 1;
}

void VoxelParticleEngine::updateGPUBuffers() {
    m_renderer.updateBuffer(m_gpuParticleBufferInvalidBegin, m_gpuParticleBufferInvalidEnd, &m_cpuParticleBuffer[m_gpuParticleBufferInvalidBegin]);

    m_gpuParticleBufferInvalid = false;
}

