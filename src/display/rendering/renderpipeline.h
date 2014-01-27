#pragma once

#include "renderpass.h"

#include <vector>
#include <memory>

class FrameBuffer;

class RenderPipeline : RenderPass {
public:
    RenderPipeline();
    virtual void apply(FrameBuffer& frameBuffer) override;
    virtual void setup() = 0;

    void addPass(std::shared_ptr<RenderPass> pass, int index=-1);

    static RenderPipeline* getDefault();
protected:
    
    std::vector<std::shared_ptr<RenderPass>> m_passes;


};