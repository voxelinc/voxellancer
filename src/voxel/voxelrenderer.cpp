#include <glow/Array.h>
#include <glow/Shader.h>
#include <glow/Texture.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glow/Shader.h>
#include <glowutils/File.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


#include "voxel/voxelrenderer.h"
#include "voxel/voxelcluster.h"
#include "camera.h"
#include "voxeleffect/mesh.h"


std::weak_ptr<VoxelRenderer> VoxelRenderer::s_instance;


VoxelRenderer::VoxelRenderer() :
    m_program(0),
    m_prepared(false),
    m_mesh()
{
    glow::debug("Create Voxelrenderer");
    createAndSetupShaders();
}


void VoxelRenderer::prepareDraw(Camera * camera, bool withBorder)
{
    m_program->setUniform("projection", camera->projection());
    m_program->setUniform("view", camera->view());
    m_program->setUniform("viewProjection", camera->viewProjection());
    m_program->setUniform("withBorder", (withBorder ? 1.0f : 0.0f));
    
    m_program->use();
    glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
    m_prepared = true;
}


void VoxelRenderer::draw(VoxelCluster * worldObject)
{
    m_program->setUniform("model", worldObject->transform().matrix());
    m_program->setUniform("emissive", worldObject->emissive());
    
    VoxelRenderData* renderData = worldObject->voxelRenderData();
    
    renderData->vertexArrayObject()->bind();
    glVertexAttribDivisor(m_program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_normal"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_position"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_color"), 1);
    renderData->vertexArrayObject()->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, renderData->voxelCount());
}


void VoxelRenderer::afterDraw()
{
    glActiveTexture(GL_TEXTURE0);
    m_program->release();
    m_prepared = false;
}

bool VoxelRenderer::prepared(){
    return m_prepared;
}

void VoxelRenderer::createAndSetupShaders() {
    glow::Shader * vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/voxelcluster.vert");
    glow::Shader * fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/voxel.frag");

    m_program = new glow::Program();
    m_program->bindAttributeLocation(0, "v_vertex");
    m_program->bindAttributeLocation(1, "v_normal");
    m_program->bindAttributeLocation(2, "v_position");
    m_program->bindAttributeLocation(3, "v_color");
    m_program->attach(vertexShader, fragmentShader);
    m_program->bindFragDataLocation(0, "fragColor");

}

glow::Program* VoxelRenderer::program() {
    assert(!s_instance.expired());
    return s_instance.lock()->m_program;
}

Mesh* VoxelRenderer::mesh() {
    assert(!s_instance.expired());
    return &s_instance.lock()->m_mesh;
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
