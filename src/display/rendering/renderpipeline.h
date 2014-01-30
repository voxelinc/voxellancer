#pragma once

#include <vector>
#include <memory>

#include "renderpass.h"


class FrameBuffer;

class RenderPipeline : RenderPass {
public:
    RenderPipeline(const std::string& name);

    virtual void apply(FrameBuffer& frameBuffer) override;
    virtual void setup() = 0;
    virtual int bufferCount() = 0;

    void add(std::shared_ptr<RenderPass> pass, int index = -1);
    void insertAfter(std::shared_ptr<RenderPass> pass, const std::string& after);


    static RenderPipeline* getDefault();

protected:
    std::vector<std::shared_ptr<RenderPass>> m_passes;
    
};