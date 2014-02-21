#include "luawrapperfunction.h"

#include <lua5.2/lua.hpp>


namespace Lua
{
    void settop(lua_State * state, int index)
    {
        lua_settop(state, index);
    }

    void pushlightuserdata(lua_State * state, void * p)
    {
        lua_pushlightuserdata(state, p);
    }

    void pushcclosure(lua_State * state, lua_CFunction fn, int n)
    {
        lua_pushcclosure(state, fn, n);
    }

    void setglobal(lua_State * state, const char * name)
    {
        lua_setglobal(state, name);
    }

    void pushnil(lua_State * state)
    {
        lua_pushnil(state);
    }
}

namespace Luaw
{
    int _lua_dispatcher(lua_State * state)
    {
        BaseLuaFunction * function = (BaseLuaFunction *) lua_touserdata(state, lua_upvalueindex(1));
        return function->apply(state);
    }

    template <>
    int _check_get<int>(lua_State * state, const int index) {
        return luaL_checkint(state, index);
    };

    template <>
    unsigned long _check_get<unsigned long>(lua_State * state, const int index) {
        return luaL_checkunsigned(state, index);
    }

    template <>
    unsigned int _check_get<unsigned int>(lua_State * state, const int index) {
        return luaL_checkunsigned(state, index);
    }

    template <>
    float _check_get<float>(lua_State * state, const int index) {
        return static_cast<float>(luaL_checknumber(state, index));
    }

    template <>
    double _check_get<double>(lua_State * state, const int index) {
        return luaL_checknumber(state, index);
    }

    template <>
    bool _check_get<bool>(lua_State * state, const int index) {
        return lua_toboolean(state, index) != 0;
    }

    template <>
    std::string _check_get<std::string>(lua_State * state, const int index) {
        return luaL_checkstring(state, index);
    }

    void _push(lua_State * /*state*/)
    {
    }

    void _push(lua_State * state, bool && value)
    {
        lua_pushboolean(state, value);
    }

    void _push(lua_State * state, int && value)
    {
        lua_pushinteger(state, value);
    }

    void _push(lua_State * state, unsigned long && value)
    {
        lua_pushunsigned(state, value);
    }

    void _push(lua_State * state, unsigned int && value)
    {
        lua_pushunsigned(state, value);
    }

    void _push(lua_State * state, float && value)
    {
        lua_pushnumber(state, value);
    }

    void _push(lua_State * state, double && value)
    {
        lua_pushnumber(state, value);
    }

    void _push(lua_State * state, std::string && value)
    {
        lua_pushlstring(state, value.c_str(), value.size());
    }
}
