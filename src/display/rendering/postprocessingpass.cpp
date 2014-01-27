#include "PostProcessingPass.h"

#include <glow/Program.h>


#include "framebuffer.h"


PostProcessingPass::PostProcessingPass(std::string name):
    RenderPass(name),
    m_program(nullptr)
{

}

void PostProcessingPass::setSampler(FrameBuffer& frameBuffer) {
    for (int i = 0; i < samplers.size();i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        frameBuffer.texture(input[i])->bind();
        m_program->setUniform<GLint>(samplers[i], i);
    }
}


void PostProcessingPass::apply(FrameBuffer& frameBuffer) {
    frameBuffer.setDrawBuffers(output);
    setSampler(frameBuffer);
    // draw m_program    
}

void PostProcessingPass::setSamplers(const std::vector<std::string>& samplers) {

}

void PostProcessingPass::setInput(const std::vector<Buffer>& input) {

}

void PostProcessingPass::setOutput(const std::vector<Buffer>& output) {

}

void PostProcessingPass::setFragmentShader(const std::string& output) {

}
