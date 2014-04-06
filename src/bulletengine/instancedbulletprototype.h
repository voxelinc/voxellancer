#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"


namespace glow {
    class Buffer;
    class Program;
    class VertexArrayObject;
}

class BulletEngineRenderer;
class Camera;
class InstancedBullet;
class VoxelMesh;
class WorldObjectBullet;

class InstancedBulletPrototype {
public:
    InstancedBulletPrototype(BulletEngineRenderer& renderer, const std::string& name);

    void add(InstancedBullet* bullet);
    void remove(InstancedBullet* bullet);

    void draw(const Camera& camera, glow::Program* program);


protected:
    bool m_initialized;

    BulletEngineRenderer& m_renderer;
    std::string m_name;
    std::unique_ptr<WorldObjectBullet> m_worldObjectBullet;

    std::stack<int> m_freeBulletSlots;

    glow::ref_ptr<glow::VertexArrayObject> m_vao;
    glow::ref_ptr<glow::Buffer> m_gridBuffer;

    glow::ref_ptr<glow::Buffer> m_gpuBulletBuffer;
    std::vector<InstancedBullet::Data> m_cpuBulletBuffer;

    void initialize();
    void initializeGrid();
    void initializeBullets();

    void allocateBulletSlots();

    void beforeContextDestroy();
    void afterContextRebuild();
};


