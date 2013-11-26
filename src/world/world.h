#pragma once
#include <memory>

class WorldLogic;
class Worldtree;
class God;


class World
{
public:
    World();
    virtual ~World();

    WorldLogic &worldLogic();
    God &god();
    Worldtree &worldtree();

    float deltaSecs() const;

    void update(float deltaSecs);

    static World *instance();

protected:
    static World *s_instance;

    std::unique_ptr<Worldtree> m_worldtree;
    std::unique_ptr<WorldLogic> m_worldLogic;
    std::unique_ptr<God> m_god;

    float m_deltaSecs;
};

