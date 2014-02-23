#pragma once

#include <list>
#include <map>
#include <memory>

#include "utils/timer.h"
#include "utils/timermanager.h"

#include "scripting/polls/eventpoll.h"


class EventPoll;
class GamePlayScript;
class World;


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

    int registerEventPoll(EventPoll* eventPoll);
    void unregisterEventPoll(int handle);

    void update(float deltaSec);


protected:
    World* m_world;
    std::list<GamePlayScript*> m_scripts;

    std::map<int, std::unique_ptr<EventPoll>> m_eventPolls;
    int m_eventPollHandleIncrementor;

    TimerManager m_timerManager;
};

