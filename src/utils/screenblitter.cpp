#include "screenblitter.h"

#include <glow/Buffer.h>
#include <glow/FrameBufferAttachment.h>
#include <glow/TextureAttachment.h>
#include <glow/VertexAttributeBinding.h>


static GLfloat screenCoords[] = {
    -1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f,  1.0f,
     1.0f, -1.0f
};

ScreenBlitter::ScreenBlitter():
    m_program(nullptr)
{
    setupGeometry();
}

void ScreenBlitter::setProgram(glow::Program* program) {
    m_program = program;
}

void ScreenBlitter::blit(glow::FrameBufferObject& fbo, const Viewport& viewport) {
    glow::FrameBufferObject::defaultFBO()->bind();

    glow::FrameBufferAttachment* fba = fbo.attachment(GL_DRAW_FRAMEBUFFER);
    assert(fba->isTextureAttachment());
    glow::Texture* texture = dynamic_cast<glow::TextureAttachment*>(fba)->texture();

    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    m_program->setUniform<GLint>("texture", 0);
    m_program->setUniform<glm::vec2>("offset", viewport.offset());
    m_program->setUniform<glm::vec2>("scale", viewport.scale());

    assert(m_program);

    m_program->use();
    m_vertexArrayObject.drawArrays(GL_TRIANGLE_STRIP, 0, 4);
    m_program->release();
}

void ScreenBlitter::setupGeometry() {
    glow::Buffer* screenCoordsBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
    screenCoordsBuffer->setData(sizeof(screenCoords), screenCoords);

    glow::VertexAttributeBinding* binding = m_vertexArrayObject.binding(0);
    binding->setAttribute(0);
    binding->setBuffer(screenCoordsBuffer, 0, sizeof(GLfloat) * 2);
    binding->setFormat(2, GL_FLOAT, GL_FALSE, 0);
    m_vertexArrayObject.enable(0);
}

