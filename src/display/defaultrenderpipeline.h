#pragma once
#include "renderpipeline.h"

#include <vector>

class FrameBuffer;
class RenderPass;

class DefaultRenderPipeline : RenderPipeline {
public:
    DefaultRenderPipeline();

    virtual void setup() override;
    
    void addBlurVertical();
    void addBlurHorizontal();
    void addBloom();
protected:
    
    std::vector<RenderPass*> m_passes;


};