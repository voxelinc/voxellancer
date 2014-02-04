#pragma once

#include "glm/glm.hpp"

class World;
class Game;

class BaseScenario {
public:
    BaseScenario(Game* game);

    void load();
    void reset();

    virtual void onKeyPressed(int key);

protected:
    Game* m_game;
    World* m_world;

    virtual void createWorld();
    virtual void populateWorld();
    virtual void clear();


    virtual void createPlanet(glm::vec3 position, int diameter, int color);
};

