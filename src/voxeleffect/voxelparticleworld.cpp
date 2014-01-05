#include "voxelparticleworld.h"

#include <iostream>

#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/File.h>

#include "voxelparticle.h"
#include "voxelmesh.h"


VoxelParticleWorld::VoxelParticleWorld():
    m_vertexBuffer(GL_ARRAY_BUFFER),
    m_normalBuffer(GL_ARRAY_BUFFER),
    m_positionBuffer(GL_ARRAY_BUFFER)
{
    loadProgram();
    setupVertexAttributes();
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

        if (voxelParticle->isDead()) {
            delete voxelParticle;
            i = m_voxelParticles.erase(i);
        } else {
            ++i;
        }
    }
}

void VoxelParticleWorld::draw(Camera& camera) {
    updateBuffers();

    m_program.setUniform("viewProjection", camera.viewProjection());

    m_program.use();
    m_vertexArrayObject.bind();
    glVertexAttribDivisor(m_program.getAttributeLocation("v_position"), 1);
    glVertexAttribDivisor(m_program.getAttributeLocation("v_orientation"), 1);
    glVertexAttribDivisor(m_program.getAttributeLocation("v_scale"), 1);
    glVertexAttribDivisor(m_program.getAttributeLocation("v_color"), 1);
    m_vertexArrayObject.drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, m_voxelParticles.size());
    m_program.release();
}

void VoxelParticleWorld::loadProgram() {
    glow::Shader* vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/voxelparticle.vert");
    glow::Shader* fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/voxelparticle.frag");

    m_program.attach(vertexShader, fragmentShader);
    m_program.bindFragDataLocation(0, "fragColor");
}

void VoxelParticleWorld::setupVertexAttributes() {
    m_vertexBuffer.setData(VoxelMesh::vertices());
    m_normalBuffer.setData(VoxelMesh::normals());

    setupVertexAttribute(m_vertexBuffer, "v_vertex", 3, GL_FLOAT, GL_TRUE, 0);
    setupVertexAttribute(m_normalBuffer, "v_normal", 3, GL_FLOAT, GL_FALSE, 1);
    setupVertexAttribute(m_positionBuffer, "v_position", 3, GL_FLOAT, GL_FALSE, 2);
    setupVertexAttribute(m_orientationBuffer, "v_orientation", 4, GL_FLOAT, GL_FALSE, 3);
    setupVertexAttribute(m_scaleBuffer, "v_scale", 1, GL_FLOAT, GL_FALSE, 4);
    setupVertexAttribute(m_colorBuffer, "v_color", 3, GL_FLOAT, GL_FALSE, 5);
}

void VoxelParticleWorld::setupVertexAttribute(glow::Buffer& buffer, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject.binding(bindingNum);
    GLint location = m_program.getAttributeLocation(name);

    binding->setAttribute(location);
    binding->setBuffer(&buffer, 0, 0);
    binding->setFormat(numPerVertex, type, normalised, 0);

    m_vertexArrayObject.enable(location);
}

void VoxelParticleWorld::updateBuffers() {
    glow::Vec3Array positions;
    glow::Array<glm::quat> orientations;
    glow::FloatArray scales;
    glow::Vec3Array colors;

    positions.reserve(m_voxelParticles.size());
    orientations.reserve(m_voxelParticles.size());
    scales.reserve(m_voxelParticles.size());
    colors.reserve(m_voxelParticles.size());

    for (VoxelParticle* voxelParticle : m_voxelParticles) {
        positions.push_back(voxelParticle->worldTransform().position());
        orientations.push_back(voxelParticle->worldTransform().orientation());
        scales.push_back(voxelParticle->worldTransform().scale());
        colors.push_back(voxelParticle->colorVec());
    }

    m_positionBuffer.setData(positions);
    m_orientationBuffer.setData(orientations);
    m_scaleBuffer.setData(scales);
    m_colorBuffer.setData(colors);
}


