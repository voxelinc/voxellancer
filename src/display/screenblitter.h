#pragma once

#include "geometry/viewport.h"

namespace glow {
    class Program;
    class FrameBufferObject;
}

class FrameBuffer;

class BlitProgram;

class ScreenBlitter {
public:
    ScreenBlitter();

    void setProgram(BlitProgram* blitProgram);

    void blit(FrameBuffer& source, const Viewport& viewport);


protected:
    BlitProgram* m_blitProgram;

};

