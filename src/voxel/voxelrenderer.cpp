#include <glow/Shader.h>
#include <glow/Texture.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glow/Uniform.h>
#include <glow/Shader.h>
#include <glowutils/global.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "camera/camera.h"

#include "voxel/voxelrenderer.h"
#include "voxel/voxelcluster.h"

#include "voxeleffect/voxelmesh.h"
#include "voxelrenderdata.h"


std::weak_ptr<VoxelRenderer> VoxelRenderer::s_instance;


VoxelRenderer::VoxelRenderer() :
    m_program(0),
    m_prepared(false),
    m_voxelMesh(new VoxelMesh()),
    m_modelMatrixUniform(nullptr),
    m_emissivenessUniform(nullptr)
{
    glow::debug("Create Voxelrenderer");
    createAndSetupShaders();
}

void VoxelRenderer::prepareDraw(const Camera& camera, bool withBorder, bool transparentPass) {
    glEnable(GL_DEPTH_TEST);

    m_program->setUniform("projection", camera.projection());
    m_program->setUniform("view", camera.view());
    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("withBorder", (withBorder ? 1.0f : 0.0f));
    m_program->setUniform("transparentPass", transparentPass);

    m_modelMatrixUniform = m_program->getUniform<glm::mat4>("model");
    m_emissivenessUniform = m_program->getUniform<float>("emissiveness");

    assert(m_modelMatrixUniform != nullptr);
    assert(m_emissivenessUniform != nullptr);

    m_program->use();

    glProvokingVertex(GL_LAST_VERTEX_CONVENTION);

    m_transparentPass = transparentPass;
    m_prepared = true;
}

void VoxelRenderer::draw(VoxelCluster& cluster) {
    m_modelMatrixUniform->set(cluster.transform().matrix());
    m_emissivenessUniform->set(cluster.emissiveness());

    VoxelRenderData* renderData = cluster.voxelRenderData();

    renderData->vertexArrayObject()->bind();
    glVertexAttribDivisor(m_program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_normal"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_position"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_color"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_emissiveness"), 1);
    if (m_transparentPass) {
        renderData->vertexArrayObject()->drawArraysInstancedBaseInstance(GL_TRIANGLE_STRIP, 0, 14, renderData->transparentVoxelCount(), renderData->transparentVoxelBase());
    } else {
        renderData->vertexArrayObject()->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, renderData->opaqueVoxelCount());
    }
}

void VoxelRenderer::afterDraw() {
    glActiveTexture(GL_TEXTURE0);
    m_program->release();
    m_prepared = false;
}

bool VoxelRenderer::prepared() {
    return m_prepared;
}

void VoxelRenderer::createAndSetupShaders() {
    m_program = new glow::Program();
    m_program->attach(
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/voxelcluster/voxelcluster.vert"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/voxelcluster/voxelcluster.frag"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/lib/voxel.frag")
    );
}

glow::Program* VoxelRenderer::program() {
    assert(!s_instance.expired());
    return s_instance.lock()->m_program;
}

VoxelMesh& VoxelRenderer::voxelMesh() {
    assert(!s_instance.expired());
    return *s_instance.lock()->m_voxelMesh;
}

std::shared_ptr<VoxelRenderer> VoxelRenderer::instance() {
    if (std::shared_ptr<VoxelRenderer> renderer = s_instance.lock()) {
        return renderer;
    } else {
        renderer = std::shared_ptr<VoxelRenderer>(new VoxelRenderer());
        s_instance = renderer;
        return renderer;
    }
}

void VoxelRenderer::beforeContextDestroy() {
    m_program = nullptr;
    m_prepared = false;
}

void VoxelRenderer::afterContextRebuild() {
    createAndSetupShaders();
}

