#include "postprocessingpass.h"

#include <assert.h>

#include <glow/Program.h>
#include <glowutils/global.h>

#include "quad.h"
#include "framebuffer.h"


PostProcessingPass::PostProcessingPass(std::string name, Quad& quad) :
    RenderPass(name),
    m_quad(quad),
    m_program(nullptr),
    m_output(),
    m_inputMapping(),
    m_fragmentShader(""),
    m_vertexShader("data/shader/screenquad.vert")
{
}

void PostProcessingPass::beforeDraw(FrameBuffer& frameBuffer) {
    frameBuffer.setDrawBuffers(m_output);
    int i = 0;
    for (std::pair<std::string, BufferName> mapping : m_inputMapping) {
        glActiveTexture(GL_TEXTURE0 + i);
        m_program->setUniform<GLint>(mapping.first, i);
        frameBuffer.texture(static_cast<int>(mapping.second))->bind();
        i++;
    }
    glDisable(GL_DEPTH_TEST);
    m_program->setUniform("viewport", frameBuffer.resolution()); frameBuffer.bind();
}


void PostProcessingPass::apply(FrameBuffer& frameBuffer) {
    if (!m_program) {
        initialize();
    }

    beforeDraw(frameBuffer);

    m_program->use();
    m_quad.draw();
    m_program->release();
}

void PostProcessingPass::setInputMapping(const std::unordered_map<std::string, BufferName>& inputMapping) {
    m_inputMapping = inputMapping;
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
