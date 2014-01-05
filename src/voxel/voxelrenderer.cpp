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


#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"
#include "voxel/voxelcluster.h"
#include "camera.h"


VoxelRenderer::VoxelRenderer() :
    m_texture(0),
    m_shaderProgram(0),
    m_vertexArrayObject(0),
    m_vertexBuffer(0),
    m_prepared(false)
{
	createAndSetupShaders();
	createAndSetupGeometry();
}


void VoxelRenderer::prepareDraw(Camera* camera, bool withBorder) {
    m_shaderProgram->setUniform("projection", camera->projection());
    m_shaderProgram->setUniform("view", camera->view());
    m_shaderProgram->setUniform("viewProjection", camera->viewProjection());
	m_shaderProgram->setUniform("withBorder", (withBorder ? 1.0f : 0.0f));

    m_shaderProgram->use();
    glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
    m_prepared = true;
}

void VoxelRenderer::draw(VoxelCluster* voxelCluster) {
    m_shaderProgram->setUniform("model", voxelCluster->transform().matrix());


    glActiveTexture(GL_TEXTURE0);
    voxelCluster->voxelRenderData()->positionTexture()->bind();
    glActiveTexture(GL_TEXTURE1);
    voxelCluster->voxelRenderData()->colorTexture()->bind();

    drawCubes(voxelCluster->voxelCount());
}


void VoxelRenderer::afterDraw() {
    glActiveTexture(GL_TEXTURE0);
    m_shaderProgram->release();
    m_prepared = false;
}

bool VoxelRenderer::prepared() {
    return m_prepared;
}

void VoxelRenderer::createAndSetupShaders() {
    glow::Shader* vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/voxelrenderer.vert");
    glow::Shader* fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/voxelrenderer.frag");

    m_shaderProgram = new glow::Program();
    m_shaderProgram->attach(vertexShader, fragmentShader);
    m_shaderProgram->bindFragDataLocation(0, "fragColor");

    m_shaderProgram->getUniform<GLint>("positionSampler")->set(0);
    m_shaderProgram->getUniform<GLint>("colorSampler")->set(1);
}

const glow::Array<glm::vec3> strip()
{
    glm::vec3 vertices[8]
    {
        glm::vec3(-.5f, -.5f, -.5f)
            , glm::vec3(-.5f, -.5f, .5f)
            , glm::vec3(-.5f, .5f, -.5f)
            , glm::vec3(-.5f, .5f, .5f)
            , glm::vec3(.5f, -.5f, -.5f)
            , glm::vec3(.5f, -.5f, .5f)
            , glm::vec3(.5f, .5f, -.5f)
            , glm::vec3(.5f, .5f, .5f)
    };

    glm::vec3 normals[7]
    {
        glm::vec3(-1, 0, 0)
            , glm::vec3(1, 0, 0)
            , glm::vec3(0, -1, 0)
            , glm::vec3(0, 1, 0)
            , glm::vec3(0, 0, -1)
            , glm::vec3(0, 0, 1)
            , glm::vec3(0, 0, 0)  // dummy
    };

    // use an interleaved array
    return glow::Array<glm::vec3>
    {
        vertices[7], normals[6]
            , vertices[3], normals[6]
            , vertices[5], normals[5]
            , vertices[1], normals[5]
            , vertices[0], normals[2]
            , vertices[3], normals[0]
            , vertices[2], normals[0]
            , vertices[7], normals[3]
            , vertices[6], normals[3]
            , vertices[5], normals[1]
            , vertices[4], normals[1]
            , vertices[0], normals[2]
            , vertices[6], normals[4]
            , vertices[2], normals[4]
    };
}

void VoxelRenderer::createAndSetupGeometry() {
/*    m_vertexArrayObject = new glow::VertexArrayObject();

    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(strip());

    auto binding0 = m_vertexArrayObject->binding(0);
    auto a_vertex = m_shaderProgram->getAttributeLocation("a_vertex");

    binding0->setAttribute(a_vertex);
    binding0->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3) * 2);
    binding0->setFormat(3, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject->enable(a_vertex);

    auto binding1 = m_vertexArrayObject->binding(1);
    auto a_normal = m_shaderProgram->getAttributeLocation("a_normal");
    binding1->setAttribute(a_normal);
    binding1->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3) * 2);
    binding1->setFormat(3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3));
    m_vertexArrayObject->enable(a_normal);
*/
}

void VoxelRenderer::drawCubes(int count) {
	
}


