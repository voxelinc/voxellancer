#pragma once

#include <list>
#include <memory>


class World;
class GamePlayScript;


/*
    Main class for accessing scripts during gameplay.
    The ScriptEngine connects Scripts with the World by tunneling events from World to the Script
    and all sorts of actions (Objectcreation, Tasks) back to the World.
*/
class ScriptEngine {
public:
    ScriptEngine(World* world);

    void startScript(GamePlayScript* script);

    void update(float deltaSec);


protected:
    World* m_world;
    std::list<GamePlayScript*> m_scripts;
};

