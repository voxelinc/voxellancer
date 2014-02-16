#pragma once

#include <list>
#include <memory>

#include "utils/timer.h"
#include "utils/timermanager.h"


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

    void registerTimer(Timer *timer);

    void update(float deltaSec);


protected:
    World* m_world;
    std::list<GamePlayScript*> m_scripts;

    TimerManager m_timerManager;
};

