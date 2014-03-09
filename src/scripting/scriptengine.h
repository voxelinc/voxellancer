#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

class AiTask;
class EventPoll;
class GamePlayScript;
class Scriptable;
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

    void addScript(std::shared_ptr<GamePlayScript> script);

    /*  start (call the "main" function) all added scripts and all future
        added scripts until stop is called */
    void start();

    /* Stops the ScriptEngine, continuing to update after start() is called again. */
    void stop();

    /*  Register/Unregister Scriptables that are managed by other objects
        and equip them with a valid scriptKey */
    void registerScriptable(Scriptable* scriptable);
    void unregisterScriptable(Scriptable* scriptable);

    template<class T>
    T* get(int key);

    void update(float deltaSec);


protected:
    World* m_world;

    std::vector<std::shared_ptr<GamePlayScript>> m_scripts;
    std::unordered_map<int, Scriptable*> m_handles;

    int m_handleKeyIncrementor;
    bool m_running;

    Scriptable* getScriptable(int key);


};

#include "scriptengine.inl"