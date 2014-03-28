#include "aabbrenderer.h"

#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/VertexArrayObject.h>

#include <glowutils/global.h>
#include <glowutils/File.h>

#include "camera/camera.h"

#include "utils/cubemesh.h"


AABBRenderer::AABBRenderer():
    m_initialized(false)
{
}

AABBRenderer::~AABBRenderer() =default;

void AABBRenderer::clear() {
    m_aabbs.clear();
}

void AABBRenderer::add(const AABB& aabb) {
    m_aabbs.push_back(std::make_pair(aabb.middle(), aabb.extent()));
}

void AABBRenderer::draw(const Camera& camera) {
    if (!m_initialized) {
        initialize();
    }

    m_aabbBuffer->setData(m_aabbs);

    m_vao->bind();
    glVertexAttribDivisor(m_program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_middle"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_extent"), 1);

    m_program->setUniform("viewProjection", camera.viewProjection());

    m_program->use();
    m_vao->drawArraysInstanced(GL_LINES, 0, m_cubeMesh->numLineVertices(), m_aabbs.size());
    m_program->release();
}

void AABBRenderer::initialize() {
    m_cubeMesh.reset(new CubeMesh());

    initializeProgram();
    initializeVAO();

    m_initialized = true;
}

void AABBRenderer::initializeProgram() {
    m_program = new glow::Program();
    m_program->attach(
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/utils/aabb.vert"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/utils/aabb.frag")
    );
}

void AABBRenderer::initializeVAO() {
    m_vao = new glow::VertexArrayObject();

    m_cubeMesh->bindLinesTo(*m_program.get(), *m_vao.get(), 0);

    m_aabbBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    int middleLocation = m_program->getAttributeLocation("v_middle");
    glow::VertexAttributeBinding* middleBinding = m_vao->binding(1);
    middleBinding->setAttribute(middleLocation);
    middleBinding->setBuffer(m_aabbBuffer, 0, sizeof(glm::vec3) * 2);
    middleBinding->setFormat(3, GL_FLOAT, GL_FALSE, 0);
    m_vao->enable(middleLocation);

    int extentLocation = m_program->getAttributeLocation("v_extent");
    glow::VertexAttributeBinding* extentBinding = m_vao->binding(2);
    extentBinding->setAttribute(extentLocation);
    extentBinding->setBuffer(m_aabbBuffer, 0, sizeof(glm::vec3) * 2);
    extentBinding->setFormat(3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3));
    m_vao->enable(extentLocation);
}


void AABBRenderer::beforeContextDestroy() {
    m_program = nullptr;
    m_vao = nullptr;
    m_aabbBuffer = nullptr;
    m_initialized = false;
}

void AABBRenderer::afterContextRebuild() {

}

