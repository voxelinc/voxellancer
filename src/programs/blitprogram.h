#pragma once

#include <glow/Program.h>
#include <glow/FrameBufferObject.h>
#include <glow/VertexArrayObject.h>

#include "geometry/viewport.h"


class BlitProgram: public glow::Program {
public:
    const GLint VERTEX_LOCATION = 0;
    const GLint TEXTURE_LOCATION = 0;

public:
    BlitProgram();
    virtual ~BlitProgram();

    void setSource(glow::FrameBufferObject* sourceFBO);
    void setDestination(glow::FrameBufferObject* targetFBO, const Viewport& m_targetViewpoer);

    virtual void blit();


protected:
    glow::VertexArrayObject m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    glow::FrameBufferObject* m_sourceFBO;
    glow::FrameBufferObject* m_destinationFBO;
    Viewport m_destinationViewport;

    bool m_initialized;


    virtual void initialize();
};

