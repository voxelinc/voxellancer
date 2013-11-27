#pragma once
#include <memory>
#include <list>

class WorldLogic;
class Worldtree;
class God;
class PhysicalVoxelCluster;

class World
{
public:
    World();
    virtual ~World();

    WorldLogic &worldLogic();
    God &god();
    Worldtree &worldtree();
    std::list<PhysicalVoxelCluster*> &clusters();

    float deltaSecs() const;

    void update(float deltaSecs);

    static World *instance();

protected:
    static World *s_instance;

    std::unique_ptr<Worldtree> m_worldtree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;
    std::list<PhysicalVoxelCluster*> m_clusters;

    float m_deltaSecs;
};

