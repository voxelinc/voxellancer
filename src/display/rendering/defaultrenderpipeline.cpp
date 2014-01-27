#include "defaultrenderpipeline.h"

#include "postprocessingpass.h"
#include "framebuffer.h"


DefaultRenderPipeline::DefaultRenderPipeline():
    RenderPipeline("defaultpipeline"),
    m_quad()
{

}

void DefaultRenderPipeline::setup() {
    addBlurVertical();
    addBlurHorizontal();
    //addBloom();
}

void DefaultRenderPipeline::addBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>("blurv", m_quad);
    pass->setSamplers({ "source" });
    pass->setInput({ Emissisiveness });
    pass->setOutput({ EmissisivenessBlur1 });
    pass->setFragmentShader("data/shader/gauss_blur_5_v.frag");
    add(pass);
}

void DefaultRenderPipeline::addBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setSamplers({ "source" });
    pass->setInput({ Color });
    pass->setOutput({ EmissisivenessBlur2 });
    pass->setFragmentShader("data/shader/gauss_blur_5_h.frag");
    add(pass);
}

void DefaultRenderPipeline::addBloom() {
    auto pass = std::make_shared<PostProcessingPass>("bloom", m_quad);
    pass->setSamplers({ "source" });
    pass->setInput({ EmissisivenessBlur2 });
    pass->setOutput({ Bloom });
    pass->setFragmentShader("data/shader/bloom.frag");
    add(pass);
}
