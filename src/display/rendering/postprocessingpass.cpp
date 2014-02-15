#include "postprocessingpass.h"

#include <assert.h>

#include <glow/Program.h>
#include <glowutils/global.h>

#include "screenquad.h"
#include "framebuffer.h"


PostProcessingPass::PostProcessingPass(const std::string& name, std::shared_ptr<ScreenQuad> quad):
    RenderPass(name),
    m_quad(quad),
    m_program(nullptr),
    m_output(),
    m_inputMapping(),
    m_fragmentShader(""),
    m_vertexShader("data/shader/postprocessing/screenquad.vert")
{
}

void PostProcessingPass::beforeDraw(FrameBuffer& frameBuffer) {
    frameBuffer.setDrawBuffers(m_output);
    int i = 0;
    for (std::pair<std::string, int> mapping : m_inputMapping) {
        glActiveTexture(GL_TEXTURE0 + i);
        m_program->setUniform<GLint>(mapping.first, i);
        frameBuffer.texture(mapping.second)->bind();
        i++;
    }
    glDisable(GL_DEPTH_TEST);
    m_program->setUniform("viewport", frameBuffer.resolution()); frameBuffer.bind();
}

void PostProcessingPass::update(float deltaSec) {

}

void PostProcessingPass::apply(FrameBuffer& frameBuffer, Camera& camera, EyeSide side) {
    if (!m_program) {
        initialize();
    }

    beforeDraw(frameBuffer);

    m_program->use();
    m_quad->draw();
    m_program->release();
}

void PostProcessingPass::setInputMapping(const std::unordered_map<std::string, int>& inputMapping) {
    m_inputMapping = inputMapping;
}

void PostProcessingPass::setOutput(const std::vector<int>& output) {
    m_output = output;
}

void PostProcessingPass::setFragmentShader(const std::string& fragmentShader) {
    m_fragmentShader = fragmentShader;
}

void PostProcessingPass::initialize() {
    m_program = new glow::Program();
    glow::Shader* vertShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, m_vertexShader);
    glow::Shader* fragShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, m_fragmentShader);

    m_program->attach(vertShader, fragShader);
    m_program->link();
    CheckGLError();
}

void PostProcessingPass::beforeContextDestroy() {
    m_program = nullptr;
}

void PostProcessingPass::afterContextRebuild() {
    initialize();
}
