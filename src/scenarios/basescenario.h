#pragma once

#include <memory>


class GamePlay;
class SpawnHelper;
class World;

class BaseScenario {
public:
    BaseScenario(GamePlay* gamePlay);
    virtual ~BaseScenario();

    void load();
    void clear();
    void reset();


protected:
    GamePlay* m_gamePlay;
    World* m_world;
    std::unique_ptr<SpawnHelper> m_spawnHelper;

    virtual void createWorld();
    virtual void populateWorld();
};

