#include "renderpipeline.h"

#include "framebuffer.h"
#include "renderpass.h"



RenderPipeline::RenderPipeline() {

}

void RenderPipeline::apply(FrameBuffer& frameBuffer) {
    for (RenderPass* pass : m_passes) {
        pass->apply(frameBuffer);
    }
}