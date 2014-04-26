#pragma once

#include <list>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "scripting/script.h"

class EventPoll;
class Scriptable;
class ScriptEngine;
class Ship;
class Squad;
class WorldObject;

class GamePlayScript: public Script {
public:
    GamePlayScript(ScriptEngine& scriptEngine, World* world = nullptr);
    GamePlayScript(ScriptEngine& scriptEngine, WorldElement* parent);
    virtual ~GamePlayScript();

    ScriptEngine& scriptEngine();
    LuaWrapper& luaWrapper();

    /**
     *  The Script hold a weak_ptr to all EventPolls to remove them
     *  from the EventPoller when the Script is destroyed.
     *  Calls addLocal(Scriptable*).
     */
    void addLocal(std::shared_ptr<EventPoll> poll);

    /**
     *  Add a Scriptable to be held by this script. On destruction of the script
     *  this Scriptable becomes invalid and will be destroyed
     */
    void addLocal(Scriptable* scriptable);


protected:
    void addGamePlayBindings();


protected:
    ScriptEngine* m_scriptEngine;
    std::vector<int> m_locals;
    std::vector<std::weak_ptr<EventPoll>> m_eventPolls;
};

