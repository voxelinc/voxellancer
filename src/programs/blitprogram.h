#pragma once

#include <iostream>

#include <glow/Program.h>
#include <glow/FrameBufferObject.h>
#include <glow/VertexArrayObject.h>

#include "geometry/viewport.h"


class BlitProgram: protected glow::Program {
public:
    const GLint VERTEX_LOCATION = 0;
    const GLint TEXTURE_LOCATION = 0;

public:
    BlitProgram();
    virtual ~BlitProgram();

    void setSource(glow::Texture* source);
    void setDestination(glow::FrameBufferObject* targetFBO, const Viewport& m_targetViewpoer);

    virtual void blit();


protected:
    glow::VertexArrayObject m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

    glow::Texture* m_source;
    glow::FrameBufferObject* m_destinationFBO;
    Viewport m_destinationViewport;

    bool m_initialized;


    virtual void initialize();
    virtual void initializeShaders() = 0;
    
    template<typename T> void setUniform(const std::string& name, const T& value);
};


#include "blitprogram.inl"
