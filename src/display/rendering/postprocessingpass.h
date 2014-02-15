#pragma once

#include <vector>
#include <unordered_map>

#include <glow/ref_ptr.h>
#include <glow/Program.h>

#include "renderpass.h"


namespace glow {
    class Program;
}

class FrameBuffer;
class ScreenQuad;

class PostProcessingPass : public RenderPass {
public:
    PostProcessingPass(const std::string& name, std::shared_ptr<ScreenQuad> quad);

    virtual void update(float deltaSec) override;
    virtual void apply(FrameBuffer& frameBuffer, const Camera& camera, EyeSide side) override;
    void beforeDraw(FrameBuffer& frameBuffer);

    void setInputMapping(const std::unordered_map<std::string, int>& inputMapping);
    void setOutput(const std::vector<int>& output);
    void setFragmentShader(const std::string& output);

    template<typename T>
    void setUniform(const std::string& name, const T& value);


protected:
    glow::ref_ptr<glow::Program> m_program;
    std::shared_ptr<ScreenQuad> m_quad;

    std::unordered_map<std::string, int> m_inputMapping;
    std::vector<int> m_output;
    std::string m_fragmentShader;
    std::string m_vertexShader;


    void initialize();
};

#include "postprocessingpass.inl"

