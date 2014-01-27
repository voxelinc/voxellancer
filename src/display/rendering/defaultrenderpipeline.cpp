#include "defaultrenderpipeline.h"

#include "postprocessingpass.h"
#include "framebuffer.h"


DefaultRenderPipeline::DefaultRenderPipeline():
    RenderPipeline("defaultpipeline")
{

}

void DefaultRenderPipeline::setup() {
    addBlurVertical();
    addBlurHorizontal();
    addBloom();
}

void DefaultRenderPipeline::addBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>("blurv");
    pass->setSamplers({ "texture" });
    pass->setInput({ Emissisiveness });
    pass->setOutput({ EmissisivenessBlur1 });
    pass->setFragmentShader("data/blurv.frag");
    add(pass);
}

void DefaultRenderPipeline::addBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>("blurh");
    pass->setSamplers({ "texture" });
    pass->setInput({ EmissisivenessBlur1 });
    pass->setOutput({ EmissisivenessBlur2 });
    pass->setFragmentShader("data/blurh.frag");
    add(pass);
}

void DefaultRenderPipeline::addBloom() {
    auto pass = std::make_shared<PostProcessingPass>("bloom");
    pass->setSamplers({ "texture" });
    pass->setInput({ EmissisivenessBlur2 });
    pass->setOutput({ Bloom });
    pass->setFragmentShader("data/bloom.frag");
    add(pass);
}
