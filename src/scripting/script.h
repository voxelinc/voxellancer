#pragma once

#include <memory>
#include <string>
#include <vector>

#include "world/worldelement.h"


class Bindings;
class LuaWrapper;

enum class ScriptState {
    Idle,
    Running,
    Stopped
};

/**
 *  Handle to a lua script
 */
class Script : public WorldElement {
public:
    explicit Script(World* world = nullptr);
    explicit Script(WorldElement* parent);
    ~Script();

    void start();
    void stop();

    ScriptState state() const;

    virtual void load(const std::string& path);
    virtual void loadString(const std::string& script);

    void update(float deltaSec);

    LuaWrapper& lua();

    const std::string& debugStatus();
    int apiSetDebugStatus(const std::string& string);


protected:
    std::unique_ptr<LuaWrapper> m_lua;
    ScriptState m_state;

    std::string m_debugStatus;
    std::vector<std::unique_ptr<Bindings>> m_bindings;


    void addBindings(Bindings* bindings);
};


