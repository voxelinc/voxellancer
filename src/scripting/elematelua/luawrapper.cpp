#include "luawrapper.h"

#include <cstdint>

#include <glow/logging.h>

#include "lua5.2/lua.hpp"


std::list<LuaWrapper *> LuaWrapper::s_instances;

LuaWrapper::LuaWrapper()
: m_state(luaL_newstate())
, m_err(LUA_OK)
{
    luaL_openlibs(m_state);
    s_instances.push_back(this);
}

LuaWrapper::~LuaWrapper()
{
    if (m_state == nullptr) return;
    s_instances.remove(this);
    m_functions.clear();
    lua_close(m_state);
}


void LuaWrapper::luaError()
{
    if (m_err != LUA_OK)
    {
        glow::critical("A Lua error occured: %;", lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
    }
}

void LuaWrapper::loadScript(const std::string & script)
{
    m_err = luaL_dofile(m_state, script.c_str());
    luaError();
    m_scripts.push_back(script);
}

void LuaWrapper::removeScript(const std::string & script)
{
    unsigned int current_position = 0;
    while (current_position < m_scripts.size())
    {
        if (m_scripts[current_position] == script)
            m_scripts.erase(m_scripts.begin()+current_position);
        else // So it won't skip future scripts with equal names
            current_position++;
    }
}

void LuaWrapper::reloadScripts()
{
    for (auto script : m_scripts)
    {
        m_err = luaL_dofile(m_state, script.c_str());
        luaError();
    }
}

void LuaWrapper::reloadAll()
{
    for (auto & instance : s_instances)
        instance->reloadScripts();
}

void LuaWrapper::pushFunc(const std::string & func) const
{
    lua_getglobal(m_state, func.c_str());
}

void LuaWrapper::callFunc(const int numArgs, const int numRet)
{
    m_err = lua_pcall(m_state, numArgs, numRet, 0);
    luaError();
}

void LuaWrapper::popStack(const int index)
{
    lua_pop(m_state, index);
}

void LuaWrapper::push() const
{
}

void LuaWrapper::push(const std::string & value) const
{
    lua_pushstring(m_state, value.c_str());
}

void LuaWrapper::push(const char * value) const
{
    lua_pushstring(m_state, value);
}

void LuaWrapper::push(const int value) const
{
    lua_pushinteger(m_state, value);
}

void LuaWrapper::push(const float value) const
{
    lua_pushnumber(m_state, value);
}

void LuaWrapper::push(const double value) const
{
    lua_pushnumber(m_state, value);
}

void LuaWrapper::push(const unsigned long value) const
{
    lua_pushunsigned(m_state, value);
}

void LuaWrapper::push(const bool value) const
{
    lua_pushboolean(m_state, value);
}


template<>
std::string LuaWrapper::fetch<std::string>(const int index) const
{
    if (!lua_isstring(m_state, index))
        glow::critical("LuaWrapper: Return value not a string.");

    return lua_tostring(m_state, index);
}

template<>
int LuaWrapper::fetch<int>(const int index) const
{
    if (!lua_isnumber(m_state, index))
        glow::critical("LuaWrapper: Return value not a number.");

    assert( static_cast<int>(lua_tointeger(m_state, index)) == lua_tointeger(m_state, index));
    return static_cast<int>(lua_tointeger(m_state, index));
}

template<>
double LuaWrapper::fetch<double>(const int index) const
{
    if (!lua_isnumber(m_state, index))
        glow::critical("LuaWrapper: Return value not a number.");

    return lua_tonumber(m_state, index);
}

template<>
float LuaWrapper::fetch<float>(const int index) const
{
    if (!lua_isnumber(m_state, index))
        glow::critical("LuaWrapper: Return value not a number.");

    return static_cast<float>(lua_tonumber(m_state, index));
}

template<>
unsigned long LuaWrapper::fetch<unsigned long>(const int index) const
{
    if (!lua_isnumber(m_state, index))
        glow::critical("LuaWrapper: Return value not a number.");

    return lua_tounsigned(m_state, index);
}

template<>
bool LuaWrapper::fetch<bool>(const int index) const
{
    if (!lua_isboolean(m_state, index))
        glow::critical("LuaWrapper: Return value not a boolean.");

    return lua_toboolean(m_state, index) != 0;
}
