#include "voxelparticleworld.h"

#include <iostream>

#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/File.h>
#include <glowutils/MathMacros.h>

#include "geometry/sphere.h"

#include "world/world.h"
#include "worldtree/worldtreequery.h"

#include "voxelparticle.h"
#include "voxelmesh.h"
#include "voxel/voxelrenderer.h"


struct ParticleData {
    glm::vec3 position;
    glm::quat orientation;
    float scale;
    int color;
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
    for (std::list<VoxelParticle*>::iterator i = m_particles.begin(); i != m_particles.end(); ) {
        VoxelParticle* voxelParticle = *i;

        voxelParticle->update(deltaSec);

        if (intersects(voxelParticle) || voxelParticle->isDead()) {
            delete voxelParticle;
            i = m_particles.erase(i);
        } else {
            ++i;
        }
    }
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
        setBufferSize(nextPowerOf2(m_particles.size()));
    }

    ParticleData* particleData = static_cast<ParticleData*>(m_particleDataBuffer->mapRange(0, m_particles.size() * sizeof(ParticleData), GL_MAP_WRITE_BIT));
    //glow::Array<ParticleData> particleData;
    //particleData.reserve(m_particles.size());

    int err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        glow::debug("map size: %; buffersize %; error code %; - %;", m_particles.size() * sizeof(ParticleData), m_particleDataBuffer->getParameter(GL_BUFFER_SIZE), err, gluErrorString(err));
        return;
    }
    glow::debug("no error");

    int i = 0;
    for (VoxelParticle* particle : m_particles) {
        particleData[i++] = (ParticleData{
            particle->worldTransform().position(),
            particle->worldTransform().orientation(),
            particle->worldTransform().scale(),
            particle->color()
        });
    }

    //m_particleDataBuffer->setData(m_particles.size() * sizeof(ParticleData), particleData.rawData(), GL_STATIC_DRAW);

    m_particleDataBuffer->unmap();
}

bool VoxelParticleWorld::intersects(VoxelParticle* voxelParticle) {
    if(!voxelParticle->intersectionCheckDue()) {
        return false;
    }
    voxelParticle->intersectionCheckPerformed();

    Sphere voxelSphere(voxelParticle->worldTransform().position(), voxelParticle->worldTransform().scale() / 2.0f);
    WorldTreeQuery worldTreeQuery(&World::instance()->worldTree(), &voxelSphere);


    return worldTreeQuery.areVoxelsIntersecting();
}

