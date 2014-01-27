#pragma once

#include <vector>
#include <glow/ref_ptr.h>

#include "renderpass.h"

namespace glow {
    class Program;
}

enum Buffer;
class FrameBuffer;



class PostProcessingPass : public RenderPass {
public:
    PostProcessingPass();

    void apply(FrameBuffer& frameBuffer);
    void setSampler(FrameBuffer& frameBuffer);

    void setSamplers(const std::vector<std::string>& samplers);
    void setInput(const std::vector<Buffer>& input);
    void setOutput(const std::vector<Buffer>& output);
    void setFragmentShader(const std::string& output);
    
protected:
    
    glow::ref_ptr<glow::Program> m_program;
    std::vector<std::string> samplers;
    std::vector<Buffer> input;
    std::vector<Buffer> output;
    std::string fragmentShader;
    std::string vertexShader;


};