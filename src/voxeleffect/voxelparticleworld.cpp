#include "voxelparticleworld.h"

#include <iostream>

#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/global.h>

#include "world/world.h"
#include "worldtree/worldtreequery.h"

#include "voxelparticle.h"
#include "voxelmesh.h"
#include "voxel/voxelrenderer.h"
#include "worldobject/worldobject.h"
#include "worldtree/worldtreegeode.h"
#include "geometry/point.h"
#include "utils/math.h"


struct ParticleData {
    glm::vec3 position;
    glm::quat orientation;
    float scale;
    int color;
    float emissiveness;
};

VoxelParticleWorld::VoxelParticleWorld():
    m_initialized(false),
    m_bufferSize(0),
    m_particles()
{

}

VoxelParticleWorld::~VoxelParticleWorld() {
    for (VoxelParticle* voxelParticle : m_particles) {
        delete voxelParticle;
    }
}

void VoxelParticleWorld::addParticle(VoxelParticle* voxelParticle) {
    m_particles.push_back(voxelParticle);
}

void VoxelParticleWorld::update(float deltaSec) {
    for (std::list<VoxelParticle*>::iterator iter = m_particles.begin(); iter != m_particles.end(); ) {
        VoxelParticle* voxelParticle = *iter;

        voxelParticle->update(deltaSec);

        if (intersects(voxelParticle) || voxelParticle->isDead()) {
            delete voxelParticle;
            iter = m_particles.erase(iter);
        } else {
            ++iter;
        }
    }
}

bool VoxelParticleWorld::intersects(VoxelParticle* voxelParticle) {
    if (!voxelParticle->intersectionCheckDue()) {
        return false;
    }
    voxelParticle->intersectionCheckPerformed();

    glm::vec3 position = voxelParticle->worldTransform().position();
    Point voxelSphere(position); // approximate a point
    WorldTreeQuery query(&World::instance()->worldTree(), &voxelSphere);

    for (WorldTreeGeode* geode : query.nearGeodes()) {
        WorldObject* worldObject = geode->worldObject();
        glm::ivec3 cell = glm::ivec3(worldObject->transform().inverseApplyTo(position));
        if (worldObject->voxel(cell)) {
            return true;
        }
    }

    return false;
}

void VoxelParticleWorld::draw(Camera& camera) {
    if(!m_initialized) {
        initialize();
    }
    if (m_particles.size() == 0) {
        return;
    }

    updateBuffers();

    m_program->setUniform("viewProjection", camera.viewProjection());

    m_program->use();
    m_vertexArrayObject->bind();
    glVertexAttribDivisor(m_program->getAttributeLocation("v_position"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_orientation"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_scale"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_color"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_emissiveness"), 1);
    m_vertexArrayObject->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, m_particles.size());
    m_program->release();
}

void VoxelParticleWorld::initialize() {
    m_program = new glow::Program();
    m_vertexArrayObject = new glow::VertexArrayObject();
    m_particleDataBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    loadProgram();
    setupVertexAttributes();
    setBufferSize(1024);

    m_initialized = true;
}

void VoxelParticleWorld::loadProgram() {
    glow::Shader* vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/particle.vert");
    glow::Shader* fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/voxel.frag");

    m_program->attach(vertexShader, fragmentShader);
    m_program->bindFragDataLocation(0, "fragColor");
    m_program->setUniform("withBorder", 1.0f);
}

void VoxelParticleWorld::setupVertexAttributes() {
    VoxelRenderer::voxelMesh()->bindTo(m_program, m_vertexArrayObject, 0);

    setupVertexAttribute(offsetof(ParticleData, position), "v_position", 3, GL_FLOAT, GL_FALSE, 2);
    setupVertexAttribute(offsetof(ParticleData, orientation), "v_orientation", 4, GL_FLOAT, GL_FALSE, 3);
    setupVertexAttribute(offsetof(ParticleData, scale), "v_scale", 1, GL_FLOAT, GL_FALSE, 4);
    setupVertexAttribute(offsetof(ParticleData, color), "v_color", GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, 5);
    setupVertexAttribute(offsetof(ParticleData, emissiveness), "v_emissiveness", 1, GL_FLOAT, GL_FALSE, 6);
}

void VoxelParticleWorld::setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(bindingNum);
    GLint location = m_program->getAttributeLocation(name);

    binding->setAttribute(location);
    binding->setBuffer(m_particleDataBuffer, 0, sizeof(ParticleData));
    binding->setFormat(numPerVertex, type, normalised, offset);

    m_vertexArrayObject->enable(location);
}

void VoxelParticleWorld::setBufferSize(int size) {
    m_bufferSize = size;
    m_particleDataBuffer->setData(m_bufferSize * sizeof(ParticleData), nullptr, GL_STREAM_DRAW);
}

void VoxelParticleWorld::updateBuffers() {
    if (m_particles.size() > m_bufferSize) {
        setBufferSize(Math::nextPowerOf2(m_particles.size()));
    }
    ParticleData* particleData = static_cast<ParticleData*>(m_particleDataBuffer->mapRange(0, m_particles.size() * sizeof(ParticleData), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));

    int i = 0;
    for (VoxelParticle* particle : m_particles) {
        particleData[i++] = ParticleData{
            particle->worldTransform().position(),
            particle->worldTransform().orientation(),
            particle->worldTransform().scale(),
            particle->color(),
            particle->emissiveness()
        };
    }

    m_particleDataBuffer->unmap();
}
