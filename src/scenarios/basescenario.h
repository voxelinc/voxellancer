#pragma once

class World;
class InGame;

class BaseScenario {
public:
    BaseScenario(InGame* inGame);

    void load();
    void reset();


protected:
    InGame* m_inGame;
    World* m_world;

    virtual void createWorld();
    virtual void populateWorld();
    virtual void clear();
};

