#include "framebuffer.h"

#include <assert.h>

#include <glow/FrameBufferObject.h>
#include <glow/Texture.h>
#include <glow/RenderBufferObject.h>
#include <glow/FrameBufferAttachment.h>
#include <glow/TextureAttachment.h>


FrameBuffer::FrameBuffer(int colorAttachments, bool depthAttachment):
    m_fbo(new glow::FrameBufferObject()),
    m_colorAttachmentCount(colorAttachments),
    m_useDepthAttachment(depthAttachment)
{
}

void FrameBuffer::setResolution(const glm::ivec2& resolution) {
    if (resolution != m_resolution) {
        m_resolution = resolution;
        setupFBO();
    }
}

void FrameBuffer::bind() {
    m_fbo->bind();
}

void FrameBuffer::unbind() {
    m_fbo->unbind();
}

void FrameBuffer::setupFBO() {
    for (int i = 0; i < m_colorAttachmentCount; i++) {
        glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);
        texture->bind();

        texture->image2D(0, GL_RGB, m_resolution.x, m_resolution.y, 0, GL_RGB, GL_FLOAT, nullptr);

        texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_fbo->attachTexture2D(GL_COLOR_ATTACHMENT0 + i, texture);
    }

    if (m_useDepthAttachment) {
        glow::RenderBufferObject* rbo = new glow::RenderBufferObject();
        rbo->storage(GL_DEPTH_COMPONENT, m_resolution.x, m_resolution.y);
        m_fbo->attachRenderBuffer(GL_DEPTH_ATTACHMENT, rbo);
    }
    m_fbo->unbind();
}

glow::FrameBufferObject& FrameBuffer::get() {
    return *m_fbo;
}

void FrameBuffer::clear() {
    m_fbo->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::setDrawBuffers(const std::vector<BufferName>& buffers) {
    std::vector<GLenum> enums;
    for (BufferName value : buffers) {
        assert(static_cast<int>(value) < m_colorAttachmentCount);
        enums.push_back(GL_COLOR_ATTACHMENT0 + static_cast<int>(value));
    }
    m_fbo->setDrawBuffers(enums);
}

glow::Texture* FrameBuffer::texture(int i) {
    assert(i < m_colorAttachmentCount);
    glow::FrameBufferAttachment* fba = m_fbo->attachment(GL_COLOR_ATTACHMENT0 + i);
    assert(fba->isTextureAttachment());
    glow::Texture* texture = dynamic_cast<glow::TextureAttachment*>(fba)->texture();
    return texture;
}

const glm::ivec2& FrameBuffer::resolution() {
    return m_resolution;
}



