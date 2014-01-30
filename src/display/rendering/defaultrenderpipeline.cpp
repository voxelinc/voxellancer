#include "defaultrenderpipeline.h"

#include "postprocessingpass.h"
#include "framebuffer.h"
#include "screenquad.h"


namespace {
    enum BufferNames {
        Default = 0,
        Color,
        NormalZ,
        Emissisiveness,
        BlurTmp,
        Bloom,
        BufferCount // should always be last member and not be used as a name
    };
}

DefaultRenderPipeline::DefaultRenderPipeline():
    RenderPipeline("defaultpipeline"),
    m_quad(std::make_shared<ScreenQuad>())
{

}

void DefaultRenderPipeline::setup() {
    addBlurVertical();
    addBlurHorizontal();
    addFinalization();
}

void DefaultRenderPipeline::addBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>("blurv", m_quad);
    pass->setInputMapping({ { "source", Emissisiveness } });
    pass->setOutput({ BlurTmp });
    pass->setFragmentShader("data/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(0, 1));
    add(pass);
}

void DefaultRenderPipeline::addBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setInputMapping({ { "source", BlurTmp } });
    pass->setOutput({ Bloom });
    pass->setFragmentShader("data/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(1, 0));
    add(pass);
}

void DefaultRenderPipeline::addFinalization() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setInputMapping({ { "color", Color }, { "bloom", Bloom } });
    pass->setOutput({ Default });
    pass->setFragmentShader("data/postprocessing/combine.frag");
    add(pass);
}

int DefaultRenderPipeline::bufferCount() {
    return BufferCount;
}

