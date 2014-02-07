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
    m_gpuParticleBufferInvalid(false),
    m_gpuParticleBufferInvalidBegin(0.0f),
    m_gpuParticleBufferInvalidEnd(0.0f),
    m_fullDeadCheckInterval("vfx.fullDeadCheckInterval"),
    m_deadCheckIndex(0),
    m_fullIntersectionCheckInterval("vfx.fullIntersectionCheckInterval"),
    m_intersectionCheckIndex(0)
{

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
    if(!m_initialized) {
        initialize();
    }

    if (m_cpuParticleBuffer.size() == 0) {
        return;
    }

    if(m_gpuParticleBufferInvalid) {
        updateGPUBuffer();
    }


    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("time", m_time);

    m_program->use();

    m_vertexArrayObject->bind();
    setupVertexAttribDivisors();
    m_vertexArrayObject->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, m_cpuParticleBuffer.size());

    m_program->release();
}

void VoxelParticleWorld::initialize() {
    m_program = new glow::Program();
    m_vertexArrayObject = new glow::VertexArrayObject();
    m_gpuParticleBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    loadProgram();
    setupVertexAttributes();
    setBufferSize(1024);

    m_initialized = true;
}

void VoxelParticleWorld::loadProgram() {
    glow::Shader* vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/particle.vert");
    glow::Shader* fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/particle.frag");

    m_program->attach(vertexShader, fragmentShader);
    m_program->bindFragDataLocation(0, "fragColor");
    m_program->setUniform("withBorder", 1.0f);
}

void VoxelParticleWorld::setupVertexAttributes() {
    VoxelRenderer::voxelMesh()->bindTo(m_program, m_vertexArrayObject, 0);

    int b = 2;

    setupVertexAttribute(offsetof(VoxelParticleData, creationPosition), "creationPosition", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, creationEulers), "creationEulers", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, creationDirectionalSpeed), "creationDirectionalSpeed", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, creationAngularSpeed), "creationAngularSpeed", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, creationTime), "creationTime", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, deathTime), "deathTime", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, scale), "scale", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, color), "color", GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, emissiveness), "emissiveness", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, directinalDampening), "directinalDampening", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, angularDampening), "angularDampening", 1, GL_FLOAT, GL_FALSE, b++);
}

void VoxelParticleWorld::setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(bindingNum);
    GLint location = m_program->getAttributeLocation(name);

    binding->setAttribute(location);
    binding->setBuffer(m_gpuParticleBuffer, 0, sizeof(VoxelParticleData));
    binding->setFormat(numPerVertex, type, normalised, offset);

    m_vertexArrayObject->enable(location);
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
    m_gpuParticleBuffer->setData(bufferSize * sizeof(VoxelParticleData), nullptr, GL_STREAM_DRAW);

    // Rather be safe than sorry for now
    m_gpuParticleBufferInvalid = true;
    m_gpuParticleBufferInvalidBegin = 0;
    m_gpuParticleBufferInvalidEnd = bufferSize - 1;
}

void VoxelParticleWorld::updateGPUBuffer() {
    int byteCount = (m_gpuParticleBufferInvalidEnd - m_gpuParticleBufferInvalidBegin + 1) * sizeof(VoxelParticleData);

    VoxelParticleData* mappedBuffer = static_cast<VoxelParticleData*>(m_gpuParticleBuffer->mapRange(
        m_gpuParticleBufferInvalidBegin * sizeof(VoxelParticleData),
        byteCount,
        GL_MAP_WRITE_BIT
    ));
    memcpy(mappedBuffer, &m_cpuParticleBuffer[m_gpuParticleBufferInvalidBegin], byteCount);
    m_gpuParticleBuffer->unmap();

    m_gpuParticleBufferInvalid = false;
}

void VoxelParticleWorld::setupVertexAttribDivisors() {
    glVertexAttribDivisor(m_program->getAttributeLocation("creationPosition"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("creationEulers"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("creationDirectionalSpeed"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("creationAngularSpeed"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("creationTime"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("deathTime"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("scale"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("color"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("emissiveness"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("directinalDampening"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("angularDampening"), 1);
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
    glm::vec3 position = (particle->directinalDampening / 2) * (timeDelta * timeDelta) +particle->creationDirectionalSpeed * timeDelta + particle->creationPosition;

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
