#pragma once

#include "postprocessingpass.h"


/**
*   the mono/stereo blitter does some additional stuff that is not usefull
*   for just copying one framebuffer to another. Please tell me if there
*   is a better way.
*/
class Blitter : public PostProcessingPass {
public:
    Blitter();
    virtual void apply(FrameBuffer& frameBuffer, glow::FrameBufferObject* target);
};