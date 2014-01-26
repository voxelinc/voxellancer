#include "renderpass.h"

#include <glow/Program.h>


#include "framebuffer.h"


RenderPass::RenderPass():
    m_program(nullptr)
{

}

void RenderPass::setSampler(FrameBuffer& frameBuffer) {
    for (int i = 0; i < samplers.size();i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        frameBuffer.texture(input[i])->bind();
        m_program->setUniform<GLint>(samplers[i], i);
    }
}


void RenderPass::apply(FrameBuffer& frameBuffer) {
    frameBuffer.setDrawBuffers(output);
    setSampler(frameBuffer);
    // draw m_program    
}

void RenderPass::setSamplers(const std::vector<std::string>& samplers) {

}

void RenderPass::setInput(const std::vector<Buffer>& input) {

}

void RenderPass::setOutput(const std::vector<Buffer>& output) {

}

void RenderPass::setFragmentShader(const std::string& output) {

}
