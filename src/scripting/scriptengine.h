#pragma once

#include <list>
#include <memory>
#include <unordered_map>


class Script;
class Scriptable;

/**
 * Main class for accessing scripts during gameplay.
 * The ScriptEngine makes Scriptables available to Scripts
 * via int-Handles
 */
class ScriptEngine {
public:
    ScriptEngine();
    virtual ~ScriptEngine();

    void registerScriptable(Scriptable* scriptable);
    void unregisterScriptable(Scriptable* scriptable);

    template<class T>
    T* get(int key);

    bool keyValid(int key) const;

    void update(float deltaSec);


protected:
    std::unordered_map<int, Scriptable*> m_scriptables;

    int m_nextKey;
    bool m_running;


    Scriptable* getScriptable(int key);
};

#include "scriptengine.inl"
