#include "blitprogram.h"

#include <iostream>

#include <glow/Buffer.h>
#include <glow/Texture.h>
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

void BlitProgram::setSource(glow::Texture* source) {
    m_source = source;
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
    
    glActiveTexture(GL_TEXTURE0);
    m_source->bind();

    setUniform<GLint>("texture", 0);
    setUniform<glm::vec2>("viewportPosition", m_destinationViewport.offset());
    setUniform<glm::vec2>("viewportSize", m_destinationViewport.scale());

    use();
    m_vertexArrayObject.drawArrays(GL_TRIANGLE_STRIP, 0, 4);
    release();
}

void BlitProgram::initialize() {
    m_initialized = true;
    
    m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);

    m_vertexBuffer->setData(sizeof(vertices), vertices);

    glow::VertexAttributeBinding* binding = m_vertexArrayObject.binding(0);
    binding->setAttribute(VERTEX_LOCATION);
    binding->setBuffer(m_vertexBuffer, 0, sizeof(GLfloat) * 2);
    binding->setFormat(2, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject.enable(VERTEX_LOCATION);

    initializeShaders();

}

