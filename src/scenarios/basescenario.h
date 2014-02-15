#pragma once

class World;
class GamePlay;

class BaseScenario {
public:
    BaseScenario(GamePlay* inGame);

    void load();
    void reset();


protected:
    GamePlay* m_inGame;
    World* m_world;

    virtual void createWorld();
    virtual void populateWorld();
    virtual void clear();
};

