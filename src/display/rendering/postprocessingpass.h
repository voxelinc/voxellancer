#pragma once

#include <vector>
#include <glow/ref_ptr.h>

#include "renderpass.h"

namespace glow {
    class Program;
}

enum BufferName;
class FrameBuffer;
class Quad;



class PostProcessingPass : public RenderPass {
public:
    PostProcessingPass(std::string name, Quad& quad);

    void apply(FrameBuffer& frameBuffer);
    void bindFrameBuffer(FrameBuffer& frameBuffer);

    void setSamplers(const std::vector<std::string>& samplers);
    void setInput(const std::vector<BufferName>& input);
    void setOutput(const std::vector<BufferName>& output);
    void setFragmentShader(const std::string& output);
    void initialize();

protected:
    glow::ref_ptr<glow::Program> m_program;
    
    std::vector<std::string> m_samplers;
    std::vector<BufferName> m_input;
    std::vector<BufferName> m_output;
    std::string m_fragmentShader;
    std::string m_vertexShader;
    Quad& m_quad;

};