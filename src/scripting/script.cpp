#include "script.h"

#include "scripting/elematelua/luawrapper.h"


Script::Script():
    m_lua(new LuaWrapper()),
    m_started(false)
{

}

Script::~Script() = default;

bool Script::started() const {
    return m_started;
}

void Script::load(const std::string& path) {
    m_lua->loadScript(path);
}

void Script::start() {
    m_lua->call("main");
    m_started = true;
}

