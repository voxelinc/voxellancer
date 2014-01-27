#pragma once

#include "renderpass.h"

#include <vector>
#include <memory>

class FrameBuffer;

class RenderPipeline : RenderPass {
public:
    RenderPipeline(std::string name);
    virtual void apply(FrameBuffer& frameBuffer) override;
    virtual void setup() = 0;

    void add(std::shared_ptr<RenderPass> pass, int index = -1);
    void insert(std::shared_ptr<RenderPass> pass, std::string after);

    static RenderPipeline* getDefault();
protected:
    
    std::vector<std::shared_ptr<RenderPass>> m_passes;


};