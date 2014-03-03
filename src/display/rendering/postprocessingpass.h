#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include <glow/ref_ptr.h>

#include "renderpass.h"
#include "etc/contextdependant.h"


namespace glow {
    class Program;
    class AbstractUniform;
}

class FrameBuffer;
class ScreenQuad;

/* 
   a configurable RenderPass for a shader that reads and
   writes on a framebuffer and has no further gamelogic
*/
class PostProcessingPass : public RenderPass, public ContextDependant {
public:
    PostProcessingPass(const std::string& name, std::shared_ptr<ScreenQuad> quad);

    virtual void apply(FrameBuffer& frameBuffer, const RenderMetaData& metadata) override;
    void beforeDraw(FrameBuffer& frameBuffer);

    void setInputMapping(const std::unordered_map<std::string, int>& inputMapping);
    void setOutput(const std::vector<int>& output);
    void setFragmentShader(const std::string& output);

    template<typename T>
    void setUniform(const std::string& name, const T& value);

    bool isEnabled();
    void setEnabled(bool enabled);

protected:
    std::unordered_map<std::string, glow::ref_ptr<glow::AbstractUniform>> m_uniforms;
    glow::ref_ptr<glow::Program> m_program;
    std::shared_ptr<ScreenQuad> m_quad;

    std::unordered_map<std::string, int> m_inputMapping;
    std::vector<int> m_output;
    std::string m_fragmentShader;
    std::string m_vertexShader;
    bool m_enabled;

    void initialize();
    void restoreUniforms();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

#include "postprocessingpass.inl"

