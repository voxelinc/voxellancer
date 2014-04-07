#pragma once

#include <memory>
#include <string>
#include <glow/ref_ptr.h>
#include <glowutils/ScreenAlignedQuad.h>

#include "etc/contextdependant.h"
#include "display/rendering/screenquad.h"
#include "camera/camera.h"


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
}

class Camera;
class VoxelRenderer;

/**
 *  Renders a texture at file on the screen quad
 *  Optionally including a status text
 */

class TextureRenderer : public ContextDependant {
public:
    TextureRenderer(const std::string& file);

    void draw();
    void drawLoading(const std::string& status);


protected:
    glow::ref_ptr<glowutils::ScreenAlignedQuad> m_quad;
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;
    std::unique_ptr<Camera> m_camera;
    std::string m_file;

    void initialize();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

