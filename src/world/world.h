#pragma once
#include <memory>
#include <list>

class WorldLogic;
class WorldTree;
class God;
class WorldObject;

class World
{
public:
    World();
    virtual ~World();

    WorldLogic &worldLogic();
    God &god();
    WorldTree &worldTree();
    std::list<WorldObject*> &clusters();

    float deltaSecs() const;

    void update(float deltaSecs);

    static World *instance();

protected:
    static World *s_instance;

    std::unique_ptr<WorldTree> m_worldTree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;
    std::list<WorldObject*> m_clusters;

    float m_deltaSecs;
};

