#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>


namespace glow {
    class FrameBufferObject;
    class Texture;
}

enum class BufferName {
    Combined = 0,
    Color,
    NormalZ,
    Emissisiveness,
    BlurTmp,
    Bloom,
};

class FrameBuffer {
public:
    FrameBuffer(int colorAttachments=1, bool depthAttachment=true);
    void bind();
    void unbind();
    void clear();

    glow::FrameBufferObject& get();
    void setDrawBuffers(std::vector<BufferName> buffers);
    
    void setResolution(const glm::ivec2& resolution);
    const glm::ivec2& resolution();

    glow::Texture* texture(int i);

protected:
    int m_colorAttachmentCount;
    bool m_useDepthAttachment;
    glm::ivec2 m_resolution;
    glow::ref_ptr<glow::FrameBufferObject> m_fbo;
    
    void setupFBO();
};