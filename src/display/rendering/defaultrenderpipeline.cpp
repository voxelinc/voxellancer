#include "defaultrenderpipeline.h"

#include "postprocessingpass.h"
#include "framebuffer.h"


DefaultRenderPipeline::DefaultRenderPipeline() {

}

void DefaultRenderPipeline::setup() {
    addBlurVertical();
    addBlurHorizontal();
    addBloom();
}

void DefaultRenderPipeline::addBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>();
    pass->setSamplers({ "texture" });
    pass->setInput({ Emissisiveness });
    pass->setOutput({ EmissisivenessBlur1 });
    pass->setFragmentShader("data/blurv.frag");
    addPass(pass);
}

void DefaultRenderPipeline::addBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>();
    pass->setSamplers({ "texture" });
    pass->setInput({ EmissisivenessBlur1 });
    pass->setOutput({ EmissisivenessBlur2 });
    pass->setFragmentShader("data/blurh.frag");
    addPass(pass);
}

void DefaultRenderPipeline::addBloom() {
    auto pass = std::make_shared<PostProcessingPass>();
    pass->setSamplers({ "texture" });
    pass->setInput({ EmissisivenessBlur2 });
    pass->setOutput({ Bloom });
    pass->setFragmentShader("data/bloom.frag");
    addPass(pass);
}
