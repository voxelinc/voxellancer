#include "framebuffer.h"

#include <glow/FrameBufferObject.h>
#include <glow/Texture.h>
#include "glow/RenderBufferObject.h"


FrameBuffer::FrameBuffer():
    m_fbo(new glow::FrameBufferObject())
{
}

void FrameBuffer::setResolution(const Size<int>& resolution) {
    m_resolution = resolution;
    setupFBO();
}

void FrameBuffer::bind() {
    m_fbo->bind();
}

void FrameBuffer::unbind() {
    m_fbo->unbind();
}

void FrameBuffer::setupFBO() {
    glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);

    texture->bind();

    texture->image2D(0, GL_RGB, m_resolution.width(), m_resolution.height(), 0, GL_RGB, GL_FLOAT, nullptr);

    texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_fbo->attachTexture2D(GL_COLOR_ATTACHMENT0, texture);

    glow::RenderBufferObject* rbo = new glow::RenderBufferObject();
    rbo->storage(GL_DEPTH_COMPONENT, m_resolution.width(), m_resolution.height());

    m_fbo->attachRenderBuffer(GL_DEPTH_ATTACHMENT, rbo);

    m_fbo->unbind();
}

glow::FrameBufferObject& FrameBuffer::get() {
    return *m_fbo;
}

void FrameBuffer::clear() {
    m_fbo->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
