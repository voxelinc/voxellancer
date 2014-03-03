#pragma once

#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

#include "iscripthandle.h"


class AiTask;
class EventPoll;
class GamePlayScript;
class Ship;
class World;
class WorldObject;


/*
    Main class for accessing scripts during gameplay.
    The ScriptEngine connects Scripts with the World by tunneling events from World to the Script
    and all sorts of actions (Objectcreation, Tasks) back to the World.
*/
class ScriptEngine {
public:
    ScriptEngine(World* world);

    ~ScriptEngine();

    void addScript(GamePlayScript* script);

    /*
        start (call the "main" function) all added scripts and all future
        added scripts until stop is called
    */
    void start();

    /*
        Stops the ScriptEngine, continuing to update after start() is called again.
    */
    void stop();

    /*
        Add/Remove Scriptables that shall be hold by the ScriptEngine
        and equip them with a valid scriptKey
    */
    void addScriptable(Scriptable* scriptable);
    void removeScriptable(Scriptable* scriptable);

    /*
        Register/Unregister Scriptables that are managed by other objects
        and equip them with a valid scriptKey
    */
    void registerScriptable(Scriptable* scriptable);
    void unregisterScriptable(Scriptable* scriptable);

    Scriptable* getScriptable(int key);
    WorldObject* getWorldObject(int key);
    Ship* getShip(int key);
    EventPoll* getEventPoll(int key);
    AiTask* getAiTask(int key);

//    void registerTimer(Timer *timer);
//
//    /*
//        Registers a worldObject and returns a key to access the worldObject from
//        a script
//    */
//    int registerWorldObject(WorldObject* worldObject);
//
//    WorldObject* getWorldObject(int handle);
//    int getWorldObjectHandle(WorldObject* worldObject);
//
//    /*
//        Adds the WorldObject (checking if it was previously added via registerWorldObject()
//        Called by God
//    */
//    void addWorldObject(WorldObject* worldObject);
//
//    /*
//        Called by God
//    */
//    void removeWorldObject(WorldObject* worldObject);
//
//    int registerEventPoll(EventPoll* eventPoll);
//    void unregisterEventPoll(int handle);

    void update(float deltaSec);


protected:
    World* m_world;

    std::list<std::unique_ptr<GamePlayScript>> m_scripts;
    std::vector<std::unique_ptr<IScriptHandle>> m_handles;
    std::list<std::unique_ptr<Scriptable>> m_scriptables;

    int m_handleKeyIncrementor;
    bool m_running;


    /*std::unordered_map<int, std::unique_ptr<EventPoll>> m_eventPolls;
    int m_eventPollHandleIncrementor;

    std::unordered_map<int, std::shared_ptr<WorldObjectScriptHandle>> m_handle2WorldObjectHandle;
    std::unordered_map<WorldObject*, std::shared_ptr<WorldObjectScriptHandle>> m_worldObject2WorldObjectHandle;
    int m_worldObjectHandleIncrementor;

    TimerManager m_timerManager;*/
};

