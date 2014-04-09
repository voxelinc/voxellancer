#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class Program;
    class VertexArrayObject;
}

class Camera;
class InstancedBullet;
class InstancedBulletContainer;
class VoxelMesh;

class BulletEngineRenderer : public ContextDependant {
public:
    BulletEngineRenderer();
    ~BulletEngineRenderer();

    int location(const std::string& attribute);

    void add(InstancedBulletContainer* container);
    void remove(InstancedBulletContainer* container);

    void draw(const Camera& camera);


protected:
    void initialize();
    void initializeProgram();

    void beforeContextDestroy() override;
    void afterContextRebuild() override;


protected:
    bool m_initialized;
    glow::ref_ptr<glow::Program> m_program;
    std::unordered_set<InstancedBulletContainer*> m_containers;
};

