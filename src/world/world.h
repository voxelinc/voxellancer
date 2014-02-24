#pragma once

#include <memory>
#include <unordered_set>


class WorldLogic;
class WorldTree;
class God;
class WorldObject;
class VoxelParticleEngine;
class Skybox;

class World
{
public:
    World();
    virtual ~World();

    Skybox &skybox();
    WorldLogic &worldLogic();
    God &god();
    WorldTree &worldTree();
    VoxelParticleEngine& particleEngine();
    std::unordered_set<WorldObject*> &worldObjects();

    void update(float deltaSecs);

    float deltaSec() const;

    static World *instance();
    static void reset();

protected:
    static World *s_instance;

    float m_deltaSec;

    std::unique_ptr<Skybox> m_skybox;
    std::unique_ptr<WorldTree> m_worldTree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;
    std::unique_ptr<VoxelParticleEngine> m_particleEngine;

    std::unordered_set<WorldObject*> m_worldObjects;

};

