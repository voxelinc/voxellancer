#include "script.h"

#include "scripting/bindings/bindings.h"
#include "scripting/elematelua/luawrapper.h"


Script::Script():
    m_lua(new LuaWrapper()),
    m_handle(this),
    m_state(ScriptState::Idle),
    m_debugStatus("")
{
    m_lua->Register("setDebugStatus", this, &Script::apiSetDebugStatus);
    load("data/scripts/vec3.lua");
}

Script::~Script() {
    m_handle.invalidate();
}

void Script::start() {
    assert(m_state == ScriptState::Idle);

    m_lua->call("main");
    m_state = ScriptState::Running;
}

void Script::stop() {
    assert(m_state == ScriptState::Running);

    m_state = ScriptState::Stopped;
}

ScriptState Script::state() const {
    return m_state;
}

void Script::load(const std::string& path) {
    m_lua->loadScript(path);
}

void Script::loadString(const std::string& script) {
    m_lua->loadString(script);
}

LuaWrapper& Script::lua() {
    return *m_lua.get();
}

Handle<Script>& Script::handle() {
    return m_handle;
}

void Script::update(float deltaSec) {
    if (m_lua->hasFunction("update")) {
        m_lua->call("update", deltaSec);
    }
}

const std::string& Script::debugStatus() {
    return m_debugStatus;
}

void Script::addBindings(Bindings* bindings) {
    m_bindings.push_back(std::unique_ptr<Bindings>(bindings));
    bindings->bind();
}

int Script::apiSetDebugStatus(const std::string& string) {
    m_debugStatus = string;
    return 0;
}

