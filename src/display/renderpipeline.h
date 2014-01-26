#pragma once

#include <vector>

class FrameBuffer;
class RenderPass;

class RenderPipeline {
public:
    RenderPipeline();
    virtual void apply(FrameBuffer& frameBuffer);
    virtual void setup() = 0;

protected:
    
    std::vector<RenderPass*> m_passes;


};