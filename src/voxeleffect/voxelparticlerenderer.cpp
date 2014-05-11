#include "voxelparticlerenderer.h"

#include <glow/Buffer.h>
#include <glow/Program.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/VertexArrayObject.h>

#include <glowutils/global.h>

#include "camera/camera.h"

#include "utils/math.h"

#include "voxelparticleengine.h"
#include "voxelmesh.h"


VoxelParticleRenderer::VoxelParticleRenderer(VoxelParticleEngine* engine):
    m_initialized(false),
    m_engine(engine),
    m_bufferSize(0),
    m_voxelMesh(new VoxelMesh()),
    m_defaultLightDir("vfx.lightdir")
{

}

VoxelParticleRenderer::~VoxelParticleRenderer() = default;

void VoxelParticleRenderer::updateBuffer(int begin, int end, VoxelParticleData* data) {
    if (!m_initialized) {
        initialize();
    }

    if(end >= m_bufferSize) {
        setBufferSize(Math::nextPowerOf2(end));
    }

    int byteCount = (end - begin + 1) * sizeof(VoxelParticleData);
    m_gpuParticleBuffer->setSubData(begin * sizeof(VoxelParticleData), byteCount, data);
}

void VoxelParticleRenderer::draw(const Camera& camera) {
    if (!m_initialized) {
        initialize();
    }

    if (m_bufferSize == 0) {
        return;
    }

    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("time", m_engine->time());
    m_program->setUniform("lightdir", m_defaultLightDir.get());

    m_program->use();

    m_vertexArrayObject->bind();
    setupVertexAttribDivisors();
    m_vertexArrayObject->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, m_bufferSize);

    m_program->release();
}

void VoxelParticleRenderer::loadProgram() {
    m_program->attach(
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/voxelparticle/voxelparticle.vert"),
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/lib/quaternion.glsl"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/voxelparticle/voxelparticle.frag"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/lib/voxel.frag")
    );

    m_program->bindFragDataLocation(0, "fragColor");
    m_program->setUniform("withBorder", 1.0f);
}

void VoxelParticleRenderer::setupVertexAttributes() {
    m_voxelMesh->bindTo(m_program, m_vertexArrayObject, 0);

    int b = 2;

    setupVertexAttribute(offsetof(VoxelParticleData, creationPosition), "creationPosition", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, creationEulers), "creationEulers", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, directionalSpeed), "directionalSpeed", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, angularSpeed), "angularSpeed", 3, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, creationTime), "creationTime", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, deathTime), "deathTime", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, scale), "scale", 1, GL_FLOAT, GL_FALSE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, color), "color", GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, b++);
    setupVertexAttribute(offsetof(VoxelParticleData, emissiveness), "emissiveness", 1, GL_FLOAT, GL_FALSE, b++);
}

void VoxelParticleRenderer::setupVertexAttribute(GLint offset, const std::string& name, int numPerVertex, GLenum type, GLboolean normalised, int bindingNum) {
    glow::VertexAttributeBinding* binding = m_vertexArrayObject->binding(bindingNum);
    GLint location = m_program->getAttributeLocation(name);

    binding->setAttribute(location);
    binding->setBuffer(m_gpuParticleBuffer, 0, sizeof(VoxelParticleData));
    binding->setFormat(numPerVertex, type, normalised, offset);

    m_vertexArrayObject->enable(location);
}

void VoxelParticleRenderer::setupVertexAttribDivisors() {
    glVertexAttribDivisor(m_program->getAttributeLocation("creationPosition"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("creationEulers"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("directionalSpeed"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("angularSpeed"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("creationTime"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("deathTime"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("scale"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("color"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("emissiveness"), 1);
}

void VoxelParticleRenderer::initialize() {
    m_program = new glow::Program();
    m_vertexArrayObject = new glow::VertexArrayObject();
    m_gpuParticleBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    loadProgram();
    setupVertexAttributes();

    setBufferSize(1024);

    m_initialized = true;
}

void VoxelParticleRenderer::setBufferSize(int bufferSize) {
    m_bufferSize = bufferSize;
    m_gpuParticleBuffer->setData(m_bufferSize * sizeof(VoxelParticleData), nullptr, GL_STREAM_DRAW);
}

void VoxelParticleRenderer::beforeContextDestroy() {
    m_vertexArrayObject = nullptr;
    m_gpuParticleBuffer = nullptr;
    m_program = nullptr;
    // trigger re-init
    m_initialized = false;
}

void VoxelParticleRenderer::afterContextRebuild() {
    // lazy init
}

