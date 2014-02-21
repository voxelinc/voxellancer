#pragma once

#if defined(MSVC)
#pragma warning (disable : 4100)
#endif

#include <string>
#include <tuple>
#include <functional>


struct lua_State;

struct BaseLuaFunction
{
    virtual ~BaseLuaFunction() {}
    virtual int apply(lua_State * state) = 0;
};

namespace Lua
{
    typedef int (*lua_CFunction) (lua_State * state);

    void settop(lua_State * state, int index);
    void pushlightuserdata(lua_State * state, void * p);
    void pushcclosure(lua_State * state, lua_CFunction fn, int n);
    void setglobal(lua_State * state, const char * name);
    void pushnil(lua_State * state);
}

namespace Luaw
{
    int _lua_dispatcher(lua_State * state);

    template <std::size_t... Is>
    struct _indices {};

    template <std::size_t N, std::size_t... Is>
    struct _indices_builder : _indices_builder<N-1, N-1, Is...> {};

    template <std::size_t... Is>
    struct _indices_builder<0, Is...>
    {
        using type = _indices<Is...>;
    };

    template <typename T> T _check_get(lua_State * state, const int index);

    void _push(lua_State * state); // Necessary in the case no arguments are passed
    void _push(lua_State * state, bool &&value);
    void _push(lua_State * state, int &&value);
    void _push(lua_State * state, unsigned long &&value);
    void _push(lua_State * state, unsigned int &&value);
    void _push(lua_State * state, float &&value);
    void _push(lua_State * state, double &&value);
    void _push(lua_State * state, std::string &&value);

    template <typename Return, typename... Args, std::size_t... N>
    Return _lift(std::function<Return(Args...)> function, std::tuple<Args...> args, _indices<N...>)
    {
        return function(std::get<N>(args)...);
    }

    template <typename Return, typename... Args>
    Return _lift(std::function<Return(Args...)> function, std::tuple<Args...> args)
    {
        return _lift(function, args, typename _indices_builder<sizeof...(Args)>::type());
    }

    template <typename... T, std::size_t... N>
    std::tuple<T...> _get_args(lua_State * state, _indices<N...>)
    {
        return std::make_tuple(_check_get<T>(state, N+1)...);
    }

    template <typename... T>
    std::tuple<T...> _get_args(lua_State * state)
    {
        const std::size_t num_args = sizeof...(T);
        return _get_args<T...>(state, typename _indices_builder<num_args>::type());
    }

    inline void _push_n(lua_State *) {}

    template <typename T, typename... Rest>
    void _push_n(lua_State * state, T value, Rest... rest)
    {
        _push(state, std::forward<T>(value));
        _push_n(state, rest...);
    }

    template <typename... T, std::size_t... N>
    void _push_dispatcher(lua_State * state, std::tuple<T...> &&values, _indices<N...>)
    {
        _push_n(state, std::get<N>(values)...);
    }

    template <typename... T>
    void _push(lua_State * state, std::tuple<T...> &&values)
    {
        const int num_values = sizeof...(T);
        Lua::settop(state, num_values);
        _push_dispatcher(state, std::forward<std::tuple<T...>>(values), typename _indices_builder<num_values>::type());
    }
}


template <int N, typename Return, typename... Args>
class LuaFunction : public BaseLuaFunction
{
protected:
    std::function<Return(Args...)> m_function;
    std::string m_name;
    lua_State ** m_state;

public:
    LuaFunction(lua_State * &state, const std::string & name, Return(*function)(Args...)) : LuaFunction(state, name, std::function<Return(Args...)>{function}) {}

    LuaFunction(lua_State * &state, const std::string & name, std::function<Return(Args...)> function) : m_function(function), m_name(name), m_state(&state)
    {
        Lua::pushlightuserdata(state, (void *)static_cast<BaseLuaFunction *>(this));

        Lua::pushcclosure(state, &Luaw::_lua_dispatcher, 1);

        Lua::setglobal(state, name.c_str());
    }

    ~LuaFunction()
    {
        if (m_state != nullptr && *m_state != nullptr)
        {
            Lua::pushnil(*m_state);
            Lua::setglobal(*m_state, m_name.c_str());
        }
    }

    int apply(lua_State * state)
    {
        std::tuple<Args...> args = Luaw::_get_args<Args...>(state);
        Return value = Luaw::_lift(m_function, args);
        Luaw::_push(state, std::forward<Return>(value));
        return N;
    }

public:
    void operator=(LuaFunction &) = delete;
};

#if defined(MSVC)
#pragma warning (default : 4100)
#endif
