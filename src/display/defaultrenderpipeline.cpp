#include "defaultrenderpipeline.h"

#include "framebuffer.h"
#include "renderpass.h"



DefaultRenderPipeline::DefaultRenderPipeline() {

}

void DefaultRenderPipeline::setup() {
    addBlurVertical();
    addBlurHorizontal();
    addBloom();
}

void DefaultRenderPipeline::addBlurVertical() {
    RenderPass* pass = new RenderPass();
    pass->setSamplers({ "texture" });
    pass->setInput({ Emissisiveness });
    pass->setOutput({ EmissisivenessBlur1 });
    pass->setFragmentShader("data/blurv.frag");
    m_passes.push_back(pass);
}

void DefaultRenderPipeline::addBlurHorizontal() {
    RenderPass* pass = new RenderPass();
    pass->setSamplers({ "texture" });
    pass->setInput({ EmissisivenessBlur1 });
    pass->setOutput({ EmissisivenessBlur2 });
    pass->setFragmentShader("data/blurh.frag");
    m_passes.push_back(pass);
}

void DefaultRenderPipeline::addBloom() {
    RenderPass* pass = new RenderPass();
    pass->setSamplers({ "texture" });
    pass->setInput({ EmissisivenessBlur2 });
    pass->setOutput({ Bloom });
    pass->setFragmentShader("data/bloom.frag");
    m_passes.push_back(pass);
}
