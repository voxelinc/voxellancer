#pragma once

#include <vector>

#include <glow/ref_ptr.h>

#include "geometry/size.h"

namespace glow {
    class FrameBufferObject;
    class Texture;
}

enum Buffer {
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
    void setDrawBuffers(std::vector<Buffer> buffers);
    void setResolution(const Size<int>& resolution);
    glow::Texture* texture(int i);

protected:
    Size<int> m_resolution;
    int m_colorAttachments;
    bool m_depthAttachment;
    glow::ref_ptr<glow::FrameBufferObject> m_fbo;
    
    void setupFBO();
};