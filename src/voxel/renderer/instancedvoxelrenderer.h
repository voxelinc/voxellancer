#pragma once

#include <string>

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
};

class Camera;
class VoxelCluster;
class VoxelMesh;

class InstancedVoxelRenderer : public ContextDependant {
public:
    InstancedVoxelRenderer();

    void prepareDraw(const Camera& camera, bool withBorder = true);
    void draw(VoxelCluster& cluster);
    void afterDraw();

    int getAttributeLocation(const std::string& name);
    glow::Program* program();

protected:
    glow::ref_ptr<glow::Program> m_program;

    void createAndSetupShaders();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;
};

