#pragma once

#include <iostream>

#include <glow/Program.h>

#include "geometry/viewport.h"
#include "etc/contextdependant.h"

namespace glow {
    class FrameBufferObject;
    class Texture;
}

class ScreenQuad;

class BlitProgram : public ContextDependant, protected glow::Program {
public:
    const GLint TEXTURE_LOCATION = 0;

    BlitProgram();
    virtual ~BlitProgram();

    void setSource(glow::Texture* source);
    void setDestination(glow::FrameBufferObject* targetFBO, const Viewport& m_targetViewpoer);

    virtual void blit();

protected:
    glow::Texture* m_source;
    glow::FrameBufferObject* m_destinationFBO;
    std::unique_ptr<ScreenQuad> m_quad;
    Viewport m_destinationViewport;
    bool m_initialized;

    virtual void initialize();
    virtual void initializeShaders() = 0;
    
    template<typename T> void setUniform(const std::string& name, const T& value);

    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};


#include "blitprogram.inl"
