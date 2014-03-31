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

/**
 *  A configurable RenderPass for a shader that reads and
 *  writes on a framebuffer and has no further gamelogic
 */
class FullTextureRenderer : public ContextDependant {
public:
    FullTextureRenderer(const std::string& filename);

    virtual void draw();

protected:
    std::unordered_map<std::string, glow::ref_ptr<glow::AbstractUniform>> m_uniforms;
    glow::ref_ptr<glow::Program> m_program;
    std::unique_ptr<ScreenQuad> m_quad;

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

