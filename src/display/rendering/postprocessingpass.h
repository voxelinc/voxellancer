#pragma once

#include <vector>
#include <unordered_map>

#include <glow/ref_ptr.h>
#include <glow/Program.h>

#include "renderpass.h"

namespace glow {
    class Program;
}

enum class BufferName;
class FrameBuffer;
class ScreenQuad;



class PostProcessingPass : public RenderPass {
public:
    PostProcessingPass(std::string name, ScreenQuad& quad);

    void apply(FrameBuffer& frameBuffer);
    void beforeDraw(FrameBuffer& frameBuffer);
    
    void setInputMapping(const std::unordered_map<std::string, BufferName>& inputMapping);
    void setOutput(const std::vector<BufferName>& output);
    void setFragmentShader(const std::string& output);

    template<typename T> 
    void setUniform(const std::string& name, const T& value);

protected:
    glow::ref_ptr<glow::Program> m_program;
    
    std::unordered_map<std::string, BufferName> m_inputMapping;
    std::vector<BufferName> m_output;
    std::string m_fragmentShader;
    std::string m_vertexShader;
    ScreenQuad& m_quad;

    void initialize();
};


template<typename T>
void PostProcessingPass::setUniform(const std::string& name, const T& value) {
    if (!m_program) {
        initialize();
    }
    m_program->setUniform(name, value);
}