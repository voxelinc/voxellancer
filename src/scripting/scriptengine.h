#pragma once

#include <list>
#include <memory>
#include <unordered_map>

class Script;
class Scriptable;

/**
 * Main class for accessing scripts during gameplay.
 * The ScriptEngine connects Scripts with the World by tunneling events from World to the Script
 * and all sorts of actions (Objectcreation, Tasks) back to the World.
 */
class ScriptEngine {
public:
    ScriptEngine();
    ~ScriptEngine();

    void addScript(std::shared_ptr<Script> script);

    /**
     * Start (call the "main" function) all added scripts and all future
     * added scripts until stop is called
     */
    void start();

    /**
     * Stops the ScriptEngine, continuing to update after start() is called again.
     */
    void stop();

    void registerScriptable(Scriptable* scriptable);

    void unregisterScriptable(Scriptable* scriptable);


    template<class T>
    T* get(int key);

    bool keyValid(int key) const;

    void update(float deltaSec);


protected:
    std::list<std::shared_ptr<Script>> m_scripts;
    std::unordered_map<int, Scriptable*> m_scriptables;

    int m_nextKey;
    bool m_running;


    Scriptable* getScriptable(int key);
    void performRemovals();
};

#include "scriptengine.inl"
