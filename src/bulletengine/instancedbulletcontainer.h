#pragma once

#include <memory>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include <glow/ref_ptr.h>

#include "utils/handle/handleowner.h"

#include "voxel/voxeldata.h"

#include "instancedbullet.h"


namespace glow {
    class Buffer;
    class Program;
    class VertexArrayObject;
}

class BulletEngine;
class Camera;
class InstancedBulletContainerRenderer;
class VoxelMesh;
class WorldObjectBullet;

class InstancedBulletContainer : public HandleOwner {
public:
    InstancedBulletContainer(BulletEngine& engine, const std::string& name);

    BulletEngine& engine();
    const std::string& name() const;

    WorldObjectBullet& prototype();

    const std::vector<VoxelData>& gridPrototype() const;

    const std::vector<InstancedBulletData>& bulletData() const;

    void add(InstancedBullet* bullet);
    void remove(InstancedBullet* bullet);

    void update(float deltaSec);

    void draw(glow::Program* program);


protected:
    void allocateSlots(int slotCount);
    void invalidateSlot(int slot);

protected:
    BulletEngine& m_engine;
    std::string m_name;
    std::unique_ptr<WorldObjectBullet> m_prototype;
    std::vector<VoxelData> m_gridPrototype;
    std::unique_ptr<InstancedBulletContainerRenderer> m_renderer;
    std::unordered_set<InstancedBullet*> m_bullets;

    std::stack<int> m_freeSlots;

    std::vector<InstancedBulletData> m_bulletData;
};


