#include "blitprogram.h"

#include <iostream>

#include <glow/Buffer.h>
#include <glow/Texture.h>
#include <glow/VertexAttributeBinding.h>
#include "display/rendering/screenquad.h"



BlitProgram::BlitProgram():
    m_initialized(false),
    m_quad(new ScreenQuad())
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
       
    glActiveTexture(GL_TEXTURE0);
    m_source->bind();

    setUniform<GLint>("texture", 0);
    setUniform<glm::vec2>("viewportPosition", m_destinationViewport.offset());
    setUniform<glm::vec2>("viewportSize", m_destinationViewport.scale());

    use();
    m_quad->draw();
    release();
}

void BlitProgram::initialize() {
    m_initialized = true;
    initializeShaders();
}

