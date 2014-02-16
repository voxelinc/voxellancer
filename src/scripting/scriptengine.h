#pragma once

#include <list>


class World;
class Script;


/*
    Main class for accessing scripts during gameplay.
    The ScriptEngine connects Scripts with the World by tunneling events from World to the Script
    and all sorts of actions (Objectcreation, Tasks) back to the World.

    Also, binds the GamePlayScriptAPI to the Scripts
*/
class ScriptEngine {
public:
    ScriptEngine(World* world);

    void startScript(Script* script);

    void update(float deltaSec);


protected:
    World* m_world;
    std::list<Script*> m_scripts;
};

