#pragma once

#include <glow/Buffer.h>
#include <glow/Program.h>
#include <glow/FrameBufferObject.h>
#include <glow/VertexArrayObject.h>

#include "geometry/viewport.h"


class glow::Program;

class ScreenBlitter {
public:
    ScreenBlitter();

    void setProgram(glow::Program* program);

    void blit(glow::FrameBufferObject& fbo, const Viewport& viewport);


protected:
    glow::Program* m_program;
    glow::VertexArrayObject m_vertexArrayObject;

    void setupGeometry();
};

