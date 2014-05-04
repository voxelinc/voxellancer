#pragma once

class World;
class GamePlay;

class BaseScenario {
public:
    BaseScenario(GamePlay* gamePlay);

    virtual void load();
    virtual void clear();
    void reset();


protected:
    GamePlay* m_gamePlay;
    World* m_world;

    virtual void createWorld();
    virtual void populateWorld();
};

