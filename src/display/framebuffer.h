#pragma once

#include <glow/ref_ptr.h>

#include "geometry/size.h"

namespace glow {
    class FrameBufferObject;
}

class FrameBuffer {
public:
    FrameBuffer();
    void bind();
    void unbind();
    void clear();

    glow::FrameBufferObject& get();
    void setResolution(const Size<int>& resolution);

protected:
    Size<int> m_resolution;
    glow::ref_ptr<glow::FrameBufferObject> m_fbo;
    
    void setupFBO();
};