#include "texturerenderer.h"

#include <stdexcept>

#include <glow/Program.hpp>
#include <glow/Texture.h>
#include <glow/Buffer.h>
#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/global.h>

#include "resource/ddstexture.h"
#include "camera/camera.h"

TextureRenderer::TextureRenderer(const std::string& file) :
    m_texture(0),
    m_shaderProgram(0),
    m_quad(),
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

void TextureRenderer::draw(const Camera& camera){
    if (!m_texture) {
        initialize();
    }
    glDisable(GL_DEPTH_TEST);

    m_texture->bind();
    m_shaderProgram->use();

    m_quad.draw();
    //m_vertexArrayObject->drawArrays(GL_TRIANGLE_FAN, 0, 4);

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
