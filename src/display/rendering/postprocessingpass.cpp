#include "PostProcessingPass.h"

#include <assert.h>

#include <glow/Program.h>
#include <glowutils/global.h>

#include "quad.h"
#include "framebuffer.h"


PostProcessingPass::PostProcessingPass(std::string name, Quad& quad) :
    RenderPass(name),
    m_quad(quad),
    m_program(nullptr),
    m_input(),
    m_output(),
    m_samplers(),
    m_fragmentShader(""),
    m_vertexShader("data/shader/screenquad.vert")
{

}

void PostProcessingPass::bindFrameBuffer(FrameBuffer& frameBuffer) {
    frameBuffer.bind();
    frameBuffer.setDrawBuffers(m_output);
    for (int i = 0; i < m_samplers.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        frameBuffer.texture(m_input[i])->bind();
        m_program->setUniform<GLint>(m_samplers[i], i);
    }
}


void PostProcessingPass::apply(FrameBuffer& frameBuffer) {
    if (!m_program) {
        initialize();
    }
    m_program->setUniform("viewport", frameBuffer.resolution());

    bindFrameBuffer(frameBuffer);
    m_program->use();
    m_quad.draw();
    m_program->release();
}

void PostProcessingPass::setSamplers(const std::vector<std::string>& samplers) {
    m_samplers = samplers;
}

void PostProcessingPass::setInput(const std::vector<BufferName>& input) {
    m_input = input;
}

void PostProcessingPass::setOutput(const std::vector<BufferName>& output) {
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
