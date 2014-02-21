#include "script.h"

#include "scripting/elematelua/luawrapper.h"


Script::Script():
    m_lua(new LuaWrapper())
{

}

Script::~Script() = default;

void Script::load(const std::string& path) {
    m_lua->loadScript(path);
}

void Script::start() {
    m_lua->call("main");
}
