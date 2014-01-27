#include "renderpipeline.h"

#include <glow/logging.h>

#include "framebuffer.h"
#include "renderpass.h"
#include "defaultrenderpipeline.h"



RenderPipeline::RenderPipeline(std::string name):
    RenderPass(name)
{
}

void RenderPipeline::apply(FrameBuffer& frameBuffer) {
    if (m_passes.size() == 0) {
        glow::debug("Renderpipeline: intializing");
        setup();
    }

    for (std::shared_ptr<RenderPass>& pass : m_passes) {
        pass->apply(frameBuffer);
    }
}

RenderPipeline* RenderPipeline::getDefault() {
    return new DefaultRenderPipeline();
}

void RenderPipeline::add(std::shared_ptr<RenderPass> pass, int index) {
    if (index == -1) {
        m_passes.push_back(pass);
    } else {
        m_passes.insert(m_passes.begin() + index, pass);
    }
}

void RenderPipeline::insert(std::shared_ptr<RenderPass> pass, std::string after) {
    auto iter = m_passes.begin();
    while (iter != m_passes.end()) {
        if ((*iter)->name() == after) {
            iter++;
            m_passes.insert(iter, pass);
            return;
        }
        iter++;
    }
    assert(false); // pass not found
}

