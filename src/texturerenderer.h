#pragma once

#include <string>
#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"
#include "display/rendering/screenquad.h"

namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
}

class Camera;

class TextureRenderer : public ContextDependant {
public:
    TextureRenderer(const std::string& file);

    void draw(const Camera& camera);


protected:
    glow::ref_ptr<glow::Texture> m_texture;
    glow::ref_ptr<glow::Program> m_shaderProgram;
    ScreenQuad m_quad;
    std::string m_file;

    void initialize();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

