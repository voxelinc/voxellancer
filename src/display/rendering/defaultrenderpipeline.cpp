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
    addFinalization();
}

void DefaultRenderPipeline::addBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>("blurv", m_quad);
    pass->setSamplers({ "source" });
    pass->setInput({ BufferName::Emissisiveness });
    pass->setOutput({ BufferName::BlurTmp });
    pass->setFragmentShader("data/shader/blur.frag");
    pass->setUniform("direction", glm::vec2(0, 1));
    add(pass);
}

void DefaultRenderPipeline::addBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setSamplers({ "source" });
    pass->setInput({ BufferName::BlurTmp });
    pass->setOutput({ BufferName::Bloom });
    pass->setFragmentShader("data/shader/blur.frag");
    pass->setUniform("direction", glm::vec2(1, 0));
    add(pass);
}

void DefaultRenderPipeline::addFinalization() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setSamplers({ "color", "bloom" });
    pass->setInput({ BufferName::Color, BufferName::Bloom });
    pass->setOutput({ BufferName::Combined });
    pass->setFragmentShader("data/shader/combine.frag");
    add(pass);
}

