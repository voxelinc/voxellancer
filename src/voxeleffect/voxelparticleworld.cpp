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


struct VoxelParticleData {
    glm::vec3 position;
    glm::quat orientation;
    float scale;
    int color;
};

VoxelParticleWorld::VoxelParticleWorld():
    m_initialized(false),
    m_bufferSize(0),
    m_voxelParticles()
{

}

VoxelParticleWorld::~VoxelParticleWorld() {
    for (VoxelParticle* voxelParticle : m_voxelParticles) {
        delete voxelParticle;
    }
}

void VoxelParticleWorld::addParticle(VoxelParticle* voxelParticle) {
    m_voxelParticles.push_back(voxelParticle);
}

void VoxelParticleWorld::update(float deltaSec) {
    for (std::list<VoxelParticle*>::iterator i = m_voxelParticles.begin(); i != m_voxelParticles.end(); ) {
        VoxelParticle* voxelParticle = *i;

        voxelParticle->update(deltaSec);

        if (intersects(voxelParticle) || voxelParticle->isDead()) {
            delete voxelParticle;
            i = m_voxelParticles.erase(i);
        } else {
            ++i;
        }
    }
}

void VoxelParticleWorld::draw(Camera& camera) {
    if(!m_initialized) {
        initialize();
    }
    if (m_voxelParticles.size() == 0) {
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
    m_vertexArrayObject->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, m_voxelParticles.size());
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

    setupVertexAttribute(offsetof(VoxelParticleData, position), "v_position", 3, GL_FLOAT, GL_FALSE, 2);
    setupVertexAttribute(offsetof(VoxelParticleData, orientation), "v_orientation", 4, GL_FLOAT, GL_FALSE, 3);
    setupVertexAttribute(offsetof(VoxelParticleData, scale), "v_scale", 1, GL_FLOAT, GL_FALSE, 4);
    setupVertexAttribute(offsetof(VoxelParticleData, color), "v_color", GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, 5);
}

void VoxelParticleWorld::setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(bindingNum);
    GLint location = m_program->getAttributeLocation(name);

    binding->setAttribute(location);
    binding->setBuffer(m_particleDataBuffer, 0, sizeof(VoxelParticleData));
    binding->setFormat(numPerVertex, type, normalised, offset);

    m_vertexArrayObject->enable(location);
}

void VoxelParticleWorld::setBufferSize(int size) {
    m_bufferSize = size;
    m_particleDataBuffer->setData(m_bufferSize * sizeof(VoxelParticleData), nullptr, GL_STREAM_DRAW);
}

void VoxelParticleWorld::updateBuffers() {
    //if (m_voxelParticles.size() > m_bufferSize) {
    //    setBufferSize(nextPowerOf2(m_voxelParticles.size()));
    //}

    //VoxelParticleData* particleData = static_cast<VoxelParticleData*>(m_particleDataBuffer->mapRange(0, m_voxelParticles.size() * sizeof(VoxelParticleData), GL_MAP_WRITE_BIT));
    glow::Array<VoxelParticleData> particleData;
    particleData.reserve(m_voxelParticles.size());


    int i = 0;
    for (VoxelParticle* voxelParticle : m_voxelParticles) {
        particleData.push_back(VoxelParticleData {
            voxelParticle->worldTransform().position(),
            voxelParticle->worldTransform().orientation(),
            voxelParticle->worldTransform().scale(),
            voxelParticle->color()
        });
    }

    m_particleDataBuffer->setData(m_voxelParticles.size() * sizeof(VoxelParticleData), particleData.rawData(), GL_STATIC_DRAW);

    //m_particleDataBuffer->unmap();
}

bool VoxelParticleWorld::intersects(VoxelParticle* voxelParticle) {
    if(!voxelParticle->intersectionCheckDue()) {
        return false;
    }
    voxelParticle->intersectionCheckPerformed();

    Sphere voxelSphere(voxelParticle->worldTransform().position(), voxelParticle->worldTransform().scale() / 2.0f);
    WorldTreeQuery worldTreeQuery((WorldTreeNode*)&World::instance()->worldTree(), &voxelSphere);


    return worldTreeQuery.areVoxelsIntersecting();
}

