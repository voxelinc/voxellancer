#include "instancedvoxelrenderer.h"


#include <glow/Array.h>
#include <glow/Shader.h>
#include <glow/Texture.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glow/Shader.h>
#include <glowutils/global.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "camera/camera.h"

#include "voxel/voxelcluster.h"

#include "voxeleffect/voxelmesh.h"
#include "voxel/voxelrenderdata.h"



InstancedVoxelRenderer::InstancedVoxelRenderer() :
m_program(0) {
    glow::debug("Create Voxelrenderer");
    createAndSetupShaders();
}

void InstancedVoxelRenderer::prepareDraw(const Camera& camera, bool withBorder) {
    glEnable(GL_DEPTH_TEST);

    m_program->setUniform("projection", camera.projection());
    m_program->setUniform("view", camera.view());
    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("withBorder", (withBorder ? 1.0f : 0.0f));

    m_program->use();

    glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
}

void InstancedVoxelRenderer::draw(VoxelCluster& cluster) {
    m_program->setUniform("model", cluster.transform().matrix());
    m_program->setUniform("emissiveness", cluster.emissiveness());


    IVoxelRenderData& renderData = cluster.voxelRenderData();

    renderData.vertexArrayObject()->bind();
    glVertexAttribDivisor(m_program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_Instanced"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_position"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_color"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_emissiveness"), 1);
    renderData.vertexArrayObject()->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, renderData.voxelCount());
}


void InstancedVoxelRenderer::afterDraw() {
    glActiveTexture(GL_TEXTURE0);
    m_program->release();
}

void InstancedVoxelRenderer::createAndSetupShaders() {
    m_program = new glow::Program();
    m_program->attach(
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/voxelcluster/voxelcluster.vert"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/voxelcluster/voxelcluster.frag"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/lib/voxel.frag")
        );
}

void InstancedVoxelRenderer::beforeContextDestroy() {
    m_program = nullptr;
}

void InstancedVoxelRenderer::afterContextRebuild() {
    createAndSetupShaders();
}

int InstancedVoxelRenderer::getAttributeLocation(const std::string& name) {
    return m_program->getAttributeLocation(name);
}

glow::Program* InstancedVoxelRenderer::program() {
    return m_program;
}
