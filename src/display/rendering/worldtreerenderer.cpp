#include "worldtreerenderer.h"

#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glow/VertexArrayBinding.h>
#include <glow/VertexArrayObject.h>

#include <glowutils/File.h>

#include "world/world.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreenode.h"



WorldTreeRenderer::WorldTreeRenderer()
{
}

void WorldTreeRenderer::draw(const Camera& camera) {
    if (!m_initialized) {
        initialize();
    }

    m_aabbs.clear();

    WorldTreeNode* root = World::instance()->worldTree().root();
    poll(camera, root);

    m_aabbBuffer->setData(m_aabbs);

    m_program->bind();
    m_vao->drawArraysInstanced(GL_LINES, 0, 14, m_aabbs.size());
    m_program->unbind();
}

void WorldTreeRenderer::poll(WorldTreeNode* node) {
    if (node->isLeaf()) {
        m_aabbs.push_back(std::make_pair(node->aabb().llf(), node->aabb().urb()));
    } else {
        for (WorldTreeNode* subnode : node->subnodes()) {
            poll(subnode);
        }
    }
}

void WorldTreeRenderer::initialize() {
    initializeProgram();
    initializeVAO();

    m_aabbMesh.reset(new AABBMesh());
    m_aabbMesh->bindTo(m_vao, m_program);
    m_wireframeBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
}

void WorldTreeRenderer::initializeProgram() {
    m_program = new glow::Program();
    m_program->attach {
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/utils/aabb.vert"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/utils/aabb.frag")
    }
}

void WorldTreeRenderer::initializeVAO() {
    m_vao = new glow::VertexArrrayObject();
    m_aabbBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    glow::VertexAttributeBinding* llfBinding = m_vao->binding(0);
    llfBinding->setAttribute(m_program->getAttributeLocation("llf"));
    llfBinding->setBuffer(m_aabbBuffer, 0, sizeof(glm::vec3) * 2);
    llfBinding->setFormat(3, GL_FLOAT, false, 0);

    glow::VertexAttributeBinding* urbBinding = m_vao->binding(1);
    urbBinding->setAttribute(m_program->getAttributeLocation("urb"));
    urbBinding->setBuffer(m_aabbBuffer,0, sizeof(glm::vec3) * 2);
    urbBinding->setFormat(3, GL_FLOAT, false, sizeof(glm::vec3));
}

