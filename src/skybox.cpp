#include "skybox.h"

#include <iostream>
#include <stdexcept>
#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/global.h>

#include "resource/ddstexture.h"

Skybox::Skybox() :
    m_texture(0),
    m_shaderProgram(0),
    m_vertexArrayObject(0),
    m_vertexBuffer(0)
{

}

void Skybox::initialize() {
    /* Texture */
    m_texture = new glow::Texture(GL_TEXTURE_CUBE_MAP);
    if (!DdsTexture::loadImageCube(m_texture,
        "data/gfx/skybox/nebula_1024_right1.dds",
        "data/gfx/skybox/nebula_1024_left2.dds",
        "data/gfx/skybox/nebula_1024_top3.dds",
        "data/gfx/skybox/nebula_1024_bottom4.dds",
        "data/gfx/skybox/nebula_1024_front5.dds",
        "data/gfx/skybox/nebula_1024_back6.dds")) {
        throw std::runtime_error("Skybox textures not found. Check working directory?");
    }
    m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_texture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    m_texture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    m_texture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    /* Shaders */
    glow::Shader* vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/skybox/skybox.vert");
    glow::Shader* fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/skybox/skybox.frag");

    m_shaderProgram = new glow::Program();
    m_shaderProgram->attach(vertexShader, fragmentShader);

    m_shaderProgram->getUniform<GLint>("texCube")->set(0);


    /* Geometry */
    auto vertices = glow::Array<glm::vec3>()
        << glm::vec3(-1, -1, 0)
        << glm::vec3(1, -1, 0)
        << glm::vec3(1, 1, 0)
        << glm::vec3(-1, 1, 0);

    m_vertexArrayObject = new glow::VertexArrayObject();

    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    m_vertexBuffer->setData(vertices);

    auto binding1 = m_vertexArrayObject->binding(0);
    auto a_vertex = m_shaderProgram->getAttributeLocation("a_vertex");

    binding1->setAttribute(a_vertex);
    binding1->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3));
    binding1->setFormat(3, GL_FLOAT, GL_FALSE, 0);

    m_vertexArrayObject->enable(a_vertex);
}

void Skybox::draw(Camera* camera){
    if (!m_texture) {
        initialize();
    }
    glDisable(GL_DEPTH_TEST);

    m_texture->bind();
    // we don't use camera->viewInverted() because the skybox does not travel with the camera
    m_shaderProgram->setUniform("viewProjectionInverted", glm::mat4_cast(camera->orientation())*glm::inverse(camera->projection()));
    m_shaderProgram->use();

    m_vertexArrayObject->drawArrays(GL_TRIANGLE_FAN, 0, 4);

    m_shaderProgram->release();
    m_texture->unbind();

    glEnable(GL_DEPTH_TEST);
}

void Skybox::beforeContextDestroy() {
    m_vertexArrayObject = nullptr;
    m_vertexBuffer = nullptr;
    m_texture = nullptr;
    m_shaderProgram = nullptr;
}

void Skybox::afterContextRebuild() {
    initialize();
}
