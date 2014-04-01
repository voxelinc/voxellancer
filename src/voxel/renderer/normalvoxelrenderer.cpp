#include "normalvoxelrenderer.h"

#include <glow/Array.h>
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

#include "voxel/voxelcluster.h"

#include "voxeleffect/voxelmesh.h"
#include "voxel/voxelrenderdata.h"



NormalVoxelRenderer::NormalVoxelRenderer() :
    m_program(0)
{
    glow::debug("Create Voxelrenderer");
    createAndSetupShaders();
}

void NormalVoxelRenderer::prepareDraw(const Camera& camera, bool withBorder) {
    glEnable(GL_DEPTH_TEST);

    m_program->setUniform("projection", camera.projection());
    m_program->setUniform("view", camera.view());
    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("withBorder", (withBorder ? 1.0f : 0.0f));

    m_modelMatrixUniform = m_program->getUniform<glm::mat4>("model");
    m_emissivenessUniform = m_program->getUniform<float>("emissiveness");

    assert(m_modelMatrixUniform != nullptr);
    assert(m_emissivenessUniform != nullptr);

    glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
}

void NormalVoxelRenderer::draw(VoxelCluster& cluster) {
    m_program->use();
    m_modelMatrixUniform->set(cluster.transform().matrix());
    m_emissivenessUniform->set(cluster.emissiveness());

    IVoxelRenderData& renderData = cluster.voxelRenderData();

    renderData.vertexArrayObject()->bind();
    glVertexAttribDivisor(m_program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_normal"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_position"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_color"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_emissiveness"), 1);
    renderData.vertexArrayObject()->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, renderData.voxelCount());
}

void NormalVoxelRenderer::afterDraw() {
    glActiveTexture(GL_TEXTURE0);
    m_program->release();
}

void NormalVoxelRenderer::createAndSetupShaders() {
    m_program = new glow::Program();
    m_program->attach(
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/voxelcluster/voxelcluster.vert"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/voxelcluster/voxelcluster.frag"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/lib/voxel.frag")
    );
}

void NormalVoxelRenderer::beforeContextDestroy() {
    m_program = nullptr;
}

void NormalVoxelRenderer::afterContextRebuild() {
    createAndSetupShaders();
}

glow::Program* NormalVoxelRenderer::program() {
    return m_program.get();
}

