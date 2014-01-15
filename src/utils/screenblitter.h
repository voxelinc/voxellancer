#pragma once

#include <glow/Buffer.h>
#include <glow/Program.h>
#include <glow/FrameBufferObject.h>

#include "geometry/viewport.h"

#include "programs/blitprogram.h"


class glow::Program;

class ScreenBlitter {
public:
    ScreenBlitter();

    void setProgram(BlitProgram* blitProgram);

    void blit(glow::FrameBufferObject& fbo, const Viewport& viewport);


protected:
    BlitProgram* m_blitProgram;

    void setupGeometry();
};

