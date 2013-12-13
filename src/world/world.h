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
    std::list<WorldObject*> &worldObjects();

    void update(float deltaSecs);

    float deltaSec() const;

    static World *instance();


protected:
    static World *s_instance;

    float m_deltaSec;

    std::unique_ptr<WorldTree> m_worldTree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;
    std::list<WorldObject*> m_worldObjects;

};

