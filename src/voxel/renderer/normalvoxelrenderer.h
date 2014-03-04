#pragma once

#include <string>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
    template<typename T>
    class Uniform;
};

class Camera;
class VoxelCluster;
class VoxelMesh;

class NormalVoxelRenderer : public ContextDependant {
public:
    NormalVoxelRenderer();

    void prepareDraw(const Camera& camera, bool withBorder = true);
    void draw(VoxelCluster& cluster);
    void afterDraw();

    glow::Program* program();

protected:
    glow::ref_ptr<glow::Program> m_program;

    glow::Uniform<glm::mat4>* m_modelMatrixUniform;
    glow::Uniform<float>* m_emissivenessUniform;

    void createAndSetupShaders();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

