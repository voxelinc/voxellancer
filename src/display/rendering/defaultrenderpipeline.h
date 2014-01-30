#pragma once

#include <vector>

#include "renderpipeline.h"
#include "screenquad.h"


class FrameBuffer;
class RenderPass;

class DefaultRenderPipeline : public RenderPipeline {
public:
    DefaultRenderPipeline();

    virtual void setup() override;
    
    void addBlurVertical();
    void addBlurHorizontal();
    void addFinalization();

protected:
    ScreenQuad m_quad;
    
};