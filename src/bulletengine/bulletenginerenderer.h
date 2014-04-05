#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class Program;
    class VertexArrayObject;
}

class Camera;
class InstancedBullet;
class InstancedBulletPrototype;
class VoxelMesh;

class BulletEngineRenderer : public ContextDependant {
public:
    BulletEngineRenderer();
    ~BulletEngineRenderer();

    void bindVoxelMeshTo(glow::VertexArrayObject* vao);

    void add(InstancedBullet* bullet);
    void remove(InstancedBullet* bullet);

    void draw(const Camera& camera);


protected:
    bool m_initialized;
    std::unordered_map<std::string, InstancedBulletPrototype*> m_prototypes;

    glow::ref_ptr<glow::Program> m_program;

    std::unique_ptr<VoxelMesh> m_voxelMesh;


    void initialize();
    void initializeProgram();

    void beforeContextDestroy() override;
    void afterContextRebuild() override;
};

