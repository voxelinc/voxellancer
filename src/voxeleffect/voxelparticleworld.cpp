#include "voxelparticleworld.h"

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


VoxelParticleWorld::VoxelParticleWorld():
    m_time(0.0f),
    m_initialized(false),
    m_renderer(this),
    m_gpuParticleBufferInvalid(false),
    m_gpuParticleBufferInvalidBegin(0.0f),
    m_gpuParticleBufferInvalidEnd(0.0f),
    m_fullDeadCheckInterval("vfx.fullDeadCheckInterval"),
    m_deadCheckIndex(0),
    m_fullIntersectionCheckInterval("vfx.fullIntersectionCheckInterval"),
    m_intersectionCheckIndex(0)
{
    setBufferSize(1024);
}

float VoxelParticleWorld::time() const {
    return m_time;
}

void VoxelParticleWorld::addParticle(const VoxelParticleSetup& particleSetup) {
    if(m_freeParticleBufferIndices.empty()) {
        setBufferSize(m_cpuParticleBuffer.size() * 2);
    }

    int bufferIndex = m_freeParticleBufferIndices.top();
    setParticleAt(particleSetup.toData(m_time), bufferIndex);
    m_freeParticleBufferIndices.pop();
}

void VoxelParticleWorld::update(float deltaSec) {
    m_time += deltaSec;

    performDeadChecks(deltaSec);
    performIntersectionChecks(deltaSec);
}

void VoxelParticleWorld::draw(Camera& camera) {
    if (m_gpuParticleBufferInvalid) {
        updateGPUBuffers();
    }

    m_renderer.draw(camera);
}

void VoxelParticleWorld::setParticleAt(const VoxelParticleData& particle, int bufferIndex) {
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

void VoxelParticleWorld::setBufferSize(int bufferSize) {
    for(int i = m_cpuParticleBuffer.size(); i < bufferSize; i++) {
        m_freeParticleBufferIndices.push(i);
    }

    m_cpuParticleBuffer.resize(bufferSize);

    // Rather be safe than sorry for now
    m_gpuParticleBufferInvalid = true;
    m_gpuParticleBufferInvalidBegin = 0;
    m_gpuParticleBufferInvalidEnd = bufferSize - 1;
}

void VoxelParticleWorld::updateGPUBuffers() {
    m_renderer.updateBuffer(m_gpuParticleBufferInvalidBegin, m_gpuParticleBufferInvalidEnd, &m_cpuParticleBuffer[m_gpuParticleBufferInvalidBegin]);

    m_gpuParticleBufferInvalid = false;
}

void VoxelParticleWorld::performDeadChecks(float deltaSec) {
    if(m_cpuParticleBuffer.empty()) {
        return;
    }

    size_t checkCount = (deltaSec * m_cpuParticleBuffer.size()) / m_fullDeadCheckInterval;
    checkCount = std::min(checkCount,  m_cpuParticleBuffer.size());

    int lastParticle = ((m_deadCheckIndex + checkCount - 1) % m_cpuParticleBuffer.size());

    for(;; m_deadCheckIndex = (m_deadCheckIndex + 1) % m_cpuParticleBuffer.size()) {
        VoxelParticleData& particle = m_cpuParticleBuffer[m_deadCheckIndex];

        if(particle.deathTime > m_time && !particle.dead) {
            particle.dead = true;
            m_freeParticleBufferIndices.push(m_deadCheckIndex);
        }

        if(m_deadCheckIndex == lastParticle) {
            break;
        }
    }
}

void VoxelParticleWorld::performIntersectionChecks(float deltaSec) {
    if(m_cpuParticleBuffer.empty()) {
        return;
    }

    size_t checkCount = (deltaSec * m_cpuParticleBuffer.size()) / m_fullIntersectionCheckInterval;
    checkCount = std::min(checkCount,  m_cpuParticleBuffer.size());

    int lastParticle = ((m_intersectionCheckIndex + checkCount - 1) % m_cpuParticleBuffer.size());

    for(;; m_intersectionCheckIndex = (m_intersectionCheckIndex + 1) % m_cpuParticleBuffer.size()) {
        VoxelParticleData& particle = m_cpuParticleBuffer[m_intersectionCheckIndex];

        if(intersects(&particle)) {
            particle.dead = true;
            m_freeParticleBufferIndices.push(m_intersectionCheckIndex);
        }

        if(m_intersectionCheckIndex == lastParticle) {
            break;
        }
    }
}

bool VoxelParticleWorld::intersects(VoxelParticleData* particle) {
	float timeDelta = m_time - particle->creationTime;
    glm::vec3 position = particle->directionalSpeed * timeDelta + particle->creationPosition;

    Point voxelPoint(position); // approximate a point
    WorldTreeQuery query(&World::instance()->worldTree(), &voxelPoint);

    for (WorldTreeGeode* geode : query.nearGeodes()) {
        WorldObject* worldObject = geode->worldObject();
        glm::ivec3 cell = glm::ivec3(worldObject->transform().inverseApplyTo(position));
        if (worldObject->voxel(cell)) {
            return true;
        }
    }

    return false;
}
