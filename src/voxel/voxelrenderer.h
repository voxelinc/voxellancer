#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
    template<typename T> class Uniform;
};

class Camera;
class VoxelCluster;
class VoxelMesh;

class VoxelRenderer : public ContextDependant {
public:
    void prepareDraw(const Camera& camera, bool withBorder = true, bool transparentPass = false);
    void draw(VoxelCluster& cluster);
    void afterDraw();

    bool prepared();

    static std::shared_ptr<VoxelRenderer> instance();
    static glow::Program* program();
    static VoxelMesh& voxelMesh();


protected:
    glow::ref_ptr<glow::Program> m_program;
    std::unique_ptr<VoxelMesh> m_voxelMesh;
    bool m_prepared;
    bool m_transparentPass;

    glow::Uniform<glm::mat4>* m_modelMatrixUniform;
    glow::Uniform<float>* m_emissivenessUniform;

    static std::weak_ptr<VoxelRenderer> s_instance;

    VoxelRenderer();
    void createAndSetupShaders();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

