#include "defaultrenderpipeline.h"

#include "postprocessingpass.h"
#include "framebuffer.h"
#include "screenquad.h"
#include "buffernames.h"


DefaultRenderPipeline::DefaultRenderPipeline() :
    RenderPipeline("defaultpipeline"),
    m_quad(std::make_shared<ScreenQuad>())
{
    
}

void DefaultRenderPipeline::setup() {
    addEmissivenessBlurVertical();
    addEmissivenessBlurHorizontal();
    addFinalization();
}

void DefaultRenderPipeline::addEmissivenessBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>("blurv", m_quad);
    pass->setInputMapping({ { "source", BufferNames::Emissisiveness } });
    pass->setOutput({ BufferNames::BlurTmp });
    pass->setFragmentShader("data/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(0, 1));
    add(pass);
}

void DefaultRenderPipeline::addEmissivenessBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setInputMapping({ { "source", BufferNames::BlurTmp } });
    pass->setOutput({ BufferNames::Bloom });
    pass->setFragmentShader("data/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(1, 0));
    add(pass);
}

void DefaultRenderPipeline::addFinalization() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setInputMapping({ { "color", BufferNames::Color }, { "bloom", BufferNames::Bloom } });
    pass->setOutput({ BufferNames::Default });
    pass->setFragmentShader("data/postprocessing/combine.frag");
    add(pass);
}

int DefaultRenderPipeline::bufferCount() {
    return BufferNames::BufferCount;
}

