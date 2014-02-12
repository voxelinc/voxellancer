#pragma once
#include <memory>

#include <glow/ref_ptr.h>

namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
};

class Camera;
class VoxelCluster;
class VoxelMesh;

class VoxelRenderer {
public:
    void prepareDraw(Camera * camera, bool withBorder = true);
    void draw(VoxelCluster * cluster);
    void afterDraw();

    bool prepared();

    static std::shared_ptr<VoxelRenderer> instance();
    static glow::Program* program();
    static VoxelMesh& voxelMesh();

private:
    glow::ref_ptr<glow::Program> m_program;
    std::unique_ptr<VoxelMesh> m_voxelMesh;
    bool m_prepared;

    static std::weak_ptr<VoxelRenderer> s_instance;

    VoxelRenderer();
    void createAndSetupShaders();
};

