#include "renderpipeline.h"

#include "framebuffer.h"
#include "renderpass.h"
#include "defaultrenderpipeline.h"



RenderPipeline::RenderPipeline() {
}

void RenderPipeline::apply(FrameBuffer& frameBuffer) {
    for (std::shared_ptr<RenderPass> pass : m_passes) {
        pass->apply(frameBuffer);
    }
}

RenderPipeline* RenderPipeline::getDefault()
{
    return new DefaultRenderPipeline();
}

void RenderPipeline::addPass(std::shared_ptr<RenderPass> pass, int index)
{
    if (index == -1){
        m_passes.push_back(pass);
    }  else {
        m_passes.insert(m_passes.begin() + index, pass);
    }
}
