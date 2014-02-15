#include "defaultrenderpipeline.h"

#include "postprocessingpass.h"
#include "framebuffer.h"
#include "screenquad.h"
#include "starfield.h"
#include "buffernames.h"


DefaultRenderPipeline::DefaultRenderPipeline(Player* player) :
    RenderPipeline("defaultpipeline"),
    m_quad(std::make_shared<ScreenQuad>()),
    m_player(player)
{

}

void DefaultRenderPipeline::setup() {
    add(std::make_shared<Starfield>(m_player));
    addBlurVertical();
    addBlurHorizontal();
    addFinalization();
}

void DefaultRenderPipeline::addBlurVertical() {
    auto pass = std::make_shared<PostProcessingPass>("blurv", m_quad);
    pass->setInputMapping({ { "source", BufferNames::Emissisiveness } });
    pass->setOutput({ BufferNames::BlurTmp });
    pass->setFragmentShader("data/shader/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(0, 1));
    add(pass);
}

void DefaultRenderPipeline::addBlurHorizontal() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setInputMapping({ { "source", BufferNames::BlurTmp } });
    pass->setOutput({ BufferNames::Bloom });
    pass->setFragmentShader("data/shader/postprocessing/blur.frag");
    pass->setUniform("direction", glm::vec2(1, 0));
    add(pass);
}

void DefaultRenderPipeline::addFinalization() {
    auto pass = std::make_shared<PostProcessingPass>("blurh", m_quad);
    pass->setInputMapping({ { "color", BufferNames::Color }, { "bloom", BufferNames::Bloom } });
    pass->setOutput({ BufferNames::Default });
    pass->setFragmentShader("data/shader/postprocessing/combine.frag");
    add(pass);
}

int DefaultRenderPipeline::bufferCount() {
    return BufferCount;
}

