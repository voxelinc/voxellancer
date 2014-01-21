#pragma once

#include "geometry/viewport.h"


namespace glow {
    class Program;
    class FrameBufferObject;
}

class BlitProgram;

class ScreenBlitter {
public:
    ScreenBlitter();

    void setProgram(BlitProgram* blitProgram);

    void blit(glow::FrameBufferObject& fbo, const Viewport& viewport);


protected:
    BlitProgram* m_blitProgram;

    void setupGeometry();
};

