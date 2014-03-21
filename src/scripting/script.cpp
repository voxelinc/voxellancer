#include "script.h"

#include "scripting/bindings/bindings.h"
#include "scripting/elematelua/luawrapper.h"


Script::Script():
    m_lua(new LuaWrapper()),
    m_started(false),
    m_debugStatus("")
{
    m_lua->Register("setDebugStatus", this, &Script::apiSetDebugStatus);
    load("data/scripts/vec3.lua");
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

void Script::update(float deltaSec) {
    if (m_lua->has("update")) {
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

