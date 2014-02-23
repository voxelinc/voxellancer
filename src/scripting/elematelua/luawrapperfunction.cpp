#include "luawrapperfunction.h"

#include <lua.hpp>

#include <glow/logging.h>

#include <glm/glm.hpp>


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

    template <>
    glm::vec3 _check_get<glm::vec3>(lua_State * state, const int index) {
        if (!lua_istable(state, index)) {
            glow::critical("LuaWrapper: Return value is not a table. (Expected table containing a vec3)");
            return glm::vec3();
        }

        glm::vec3 v;
        int v_index = 0;
        lua_pushnil(state);
        while (lua_next(state, index) != 0) {
            if (!lua_isnumber(state, -1))
                glow::critical("LuaWrapper: Return table value is not number, while trying to read a vec3.");
            else
                if (v_index < 3)   // only try to copy the value into the vector if size table has not more than 3 entries
                    v[v_index] = static_cast<float>(lua_tonumber(state, -1));
            ++v_index;
            lua_pop(state, 1);
            if (v_index > 3) {
                glow::critical("LuaWrapper: Return table larger than expected, while trying to read a vec3.");
                break;
            }
        }

        return v;
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
