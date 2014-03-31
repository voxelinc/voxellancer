#include "script.h"

#include "scripting/elematelua/luawrapper.h"


Script::Script():
    m_lua(new LuaWrapper()),
    m_handle(this),
    m_started(false),
    m_debugStatus("")
{
    m_lua->Register("setDebugStatus", this, &Script::apiSetDebugStatus);
    load("data/scripts/vec3.lua");
}

Script::~Script() {
    m_handle.invalidate();
}

bool Script::started() const {
    return m_started;
}

void Script::load(const std::string& path) {
    m_lua->loadScript(path);
}

void Script::loadString(const std::string& script) {
    m_lua->loadString(script);
}

void Script::start() {
    m_lua->call("main");
    m_started = true;
}

LuaWrapper& Script::lua() {
    return *m_lua.get();
}

Handle<Script>& Script::handle() {
    return m_handle;
}

const std::string& Script::debugStatus() {
    return m_debugStatus;
}

int Script::apiSetDebugStatus(const std::string& string) {
    m_debugStatus = string;
    return 0;
}

