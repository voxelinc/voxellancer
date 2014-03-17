#include "defaultrenderpipeline.h"

#include "postprocessingpass.h"
#include "framebuffer.h"
#include "screenquad.h"
#include "buffernames.h"


DefaultRenderPipeline::DefaultRenderPipeline() :
    RenderPipeline("defaultpipeline"),
    m_antialiasing("vfx.antialiasing"),
    m_fxaa(nullptr),
    m_finalization(nullptr),
    m_quad(std::make_shared<ScreenQuad>())
{
    
}

void DefaultRenderPipeline::apply(FrameBuffer& frameBuffer, const RenderMetaData& metadata) {
    RenderPipeline::apply(frameBuffer, metadata);
    
    bool useFxaa = m_antialiasing.get() == "fxaa";
    if (useFxaa != m_fxaa->isEnabled()) {
        m_fxaa->setEnabled(useFxaa);
        if (useFxaa) { // rewire buffer for fxaa
            m_finalization->setInputMapping({ { "color", BufferNames::FXAA }, { "bloom", BufferNames::Bloom } });
        } else {
            m_finalization->setInputMapping({ { "color", BufferNames::Color }, { "bloom", BufferNames::Bloom } });
        }
    }
}

void DefaultRenderPipeline::setup() {
    addFXAA();
    addEmissivenessBlurVertical();
    addEmissivenessBlurHorizontal();
    addFinalization();
}

void DefaultRenderPipeline::addFXAA() {
    m_fxaa = std::make_shared<PostProcessingPass>("fxaa", m_quad);
    m_fxaa->setInputMapping({ { "source", BufferNames::Color } });
    m_fxaa->setOutput({ BufferNames::FXAA });
    m_fxaa->setFragmentShader("data/shader/postprocessing/fxaa.frag");
    m_fxaa->setEnabled(false);
    add(m_fxaa);
}

void DefaultRenderPipeline::addEmissivenessBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>("blurv", m_quad);
    pass->setInputMapping({ { "source", BufferNames::Emissisiveness } });
    pass->setOutput({ BufferNames::BlurTmp });
    pass->setFragmentShader("data/shader/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(0, 1));
    add(pass);
}

void DefaultRenderPipeline::addEmissivenessBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setInputMapping({ { "source", BufferNames::BlurTmp } });
    pass->setOutput({ BufferNames::Bloom });
    pass->setFragmentShader("data/shader/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(1, 0));
    add(pass);
}

void DefaultRenderPipeline::addFinalization() {
    m_finalization = std::make_shared<PostProcessingPass>("blurh", m_quad);
    m_finalization->setInputMapping({ { "color", BufferNames::Color }, { "bloom", BufferNames::Bloom } });
    m_finalization->setOutput({ BufferNames::Default });
    m_finalization->setFragmentShader("data/shader/postprocessing/combine.frag");
    add(m_finalization);
}

int DefaultRenderPipeline::bufferCount() {
    return BufferNames::BufferCount;
}
