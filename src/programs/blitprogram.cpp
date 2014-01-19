#include "blitprogram.h"

#include <iostream>

#include <glow/Buffer.h>
#include <glow/Texture.h>
#include <glow/TextureAttachment.h>
#include <glow/FrameBufferAttachment.h>
#include <glow/VertexAttributeBinding.h>


static GLfloat vertices[] = {
    -1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f,  1.0f,
     1.0f, -1.0f
};

BlitProgram::BlitProgram():
    m_initialized(false)
{
}

BlitProgram::~BlitProgram() {

}

void BlitProgram::setSource(glow::FrameBufferObject* sourceFBO) {
    m_sourceFBO = sourceFBO;
}

void BlitProgram::setDestination(glow::FrameBufferObject* destinationFBO, const Viewport& destinationViewport) {
    m_destinationFBO = destinationFBO;
    m_destinationViewport = destinationViewport;
}

void BlitProgram::blit() {
    if(!m_initialized) {
        initialize();
    }

    m_destinationFBO->bind();

    glow::FrameBufferAttachment* fba = m_sourceFBO->attachment(GL_COLOR_ATTACHMENT0);
    assert(fba->isTextureAttachment());

    glow::Texture* texture = dynamic_cast<glow::TextureAttachment*>(fba)->texture();

    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    setUniform<GLint>("texture", 0);
    setUniform<glm::vec2>("viewportPosition", m_destinationViewport.offset());
    setUniform<glm::vec2>("viewportSize", m_destinationViewport.scale());

    use();
    m_vertexArrayObject.drawArrays(GL_TRIANGLE_STRIP, 0, 4);
    release();
}

void BlitProgram::initialize() {
    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    m_vertexBuffer->setData(sizeof(vertices), vertices);

    glow::VertexAttributeBinding* binding = m_vertexArrayObject.binding(0);
    binding->setAttribute(VERTEX_LOCATION);
    binding->setBuffer(m_vertexBuffer, 0, sizeof(GLfloat) * 2);
    binding->setFormat(2, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject.enable(VERTEX_LOCATION);

    m_initialized = true;
}

