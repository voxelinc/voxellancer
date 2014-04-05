#include "texturerenderer.h"

#include <stdexcept>

#include <GL/glew.h>

#ifdef WIN32
#include <GL/wglew.h>
#endif
#include <GLFW/glfw3.h>

#include <glow/Program.hpp>
#include <glow/Texture.h>
#include <glow/Buffer.h>
#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/global.h>

#include "resource/ddstexture.h"
#include "voxel/voxelrenderer.h"
#include "ui/voxelfont.h"
#include "etc/contextprovider.h"

TextureRenderer::TextureRenderer(const std::string& file) :
    m_texture(0),
    m_shaderProgram(0),
    m_quad(new ScreenQuad()),
    m_camera(new Camera(ContextProvider::instance()->viewport().width(), ContextProvider::instance()->viewport().height())),
    m_voxelRenderer(VoxelRenderer::instance()), // we hold this pointer to avoid the VR being recreated each time
    m_file(file)
{
}

void TextureRenderer::initialize() {
    /* Texture */
    m_texture = new glow::Texture(GL_TEXTURE_2D);
    if (!DdsTexture::loadImage2d(m_texture, m_file)) {
        throw std::runtime_error("Texture not found. Check working directory?");
    }
    m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_texture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    m_texture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    m_texture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    /* Shaders */
    glow::Shader* vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/texturerenderer/texturerenderer.vert");
    glow::Shader* fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/texturerenderer/texturerenderer.frag");

    m_shaderProgram = new glow::Program();
    m_shaderProgram->attach(vertexShader, fragmentShader);

    m_shaderProgram->getUniform<GLint>("tex")->set(0); 
}

void TextureRenderer::drawLoading(const std::string& status) {
    draw();
    m_voxelRenderer->prepareDraw(*m_camera.get(), false);
    m_voxelRenderer->program()->getUniform<glm::vec3>("lightdir")->set(glm::vec3(0, 0, 1));
    VoxelFont::instance()->drawString("Voxellancer", glm::vec3(0, 0.5f, -1) * 40.f, glm::quat(), FontSize::SIZE5x7, 0.4f, FontAlign::CENTER);
    VoxelFont::instance()->drawString(status, glm::vec3(-0.85f, -0.5f, -1) * 40.f, glm::quat(), FontSize::SIZE5x7, 0.15f, FontAlign::LEFT);
    m_voxelRenderer->afterDraw();
    glfwSwapBuffers(glfwGetCurrentContext());
}

void TextureRenderer::draw(){
    if (!m_texture) {
        initialize();
    }
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    m_texture->bind();
    m_shaderProgram->use();

    m_quad->draw();

    m_shaderProgram->release();
    m_texture->unbind();

    glEnable(GL_DEPTH_TEST);
}

void TextureRenderer::beforeContextDestroy() {
    m_texture = nullptr;
    m_shaderProgram = nullptr;
}

void TextureRenderer::afterContextRebuild() {
    initialize();
}
