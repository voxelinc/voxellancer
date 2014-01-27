#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>


namespace glow {
    class FrameBufferObject;
    class Texture;
}

enum BufferName {
    Color = 0,
    NormalZ = 1,
    Emissisiveness = 2,
    EmissisivenessBlur1 = 3,
    EmissisivenessBlur2 = 4,
    Bloom = 5,
    Combined = 6
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