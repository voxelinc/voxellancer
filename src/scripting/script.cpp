#include "script.h"

#include "scripting/elematelua/luawrapper.h"


Script::Script():
    m_lua(new LuaWrapper()),
    m_started(false),
    m_debugStatus("")
{
    m_lua->Register("setDebugStatus", this, &Script::apiSetDebugStatus);
}

Script::~Script() = default;

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


const std::string& Script::debugStatus() {
    return m_debugStatus;
}

int Script::apiSetDebugStatus(const std::string& string) {
    m_debugStatus = string;
    return 0;
}
