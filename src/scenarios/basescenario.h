#pragma once

class World;
class Game;

class BaseScenario {
public:
    BaseScenario(Game* game);

    void load();
    void clear();
    void reset();


protected:
    Game* m_game;
    World* m_world;

    virtual void createWorld();
    virtual void populateWorld();
};

