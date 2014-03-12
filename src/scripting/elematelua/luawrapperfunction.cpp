#include "luawrapperfunction.h"

#include <lua5.2/lua.hpp>

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

        float x = _check_get_field<float>(state, index, "x");
        float y = _check_get_field<float>(state, index, "y");
        float z = _check_get_field<float>(state, index, "z");

        return glm::vec3(x,y,z);
    }

    template <typename T>
    T _check_get_field(lua_State * state, const int index, const char* key) {
        assert(lua_istable(state, index));
        lua_pushstring(state, key); 
        lua_gettable(state, index);  // pop key, push table[key] on stack
        T result = _check_get<T>(state, -1);
        lua_pop(state, 1);  // remove table[key] from stack
        return result;
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

    void _push(lua_State * state, glm::vec3 && value)
    {
        lua_newtable(state);
        lua_pushnumber(state, value.x);
        lua_setfield(state, -2, "x");
        lua_pushnumber(state, value.y);
        lua_setfield(state, -2, "y");
        lua_pushnumber(state, value.z);
        lua_setfield(state, -2, "z");
    }

}
