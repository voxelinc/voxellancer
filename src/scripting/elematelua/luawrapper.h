#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <list>
#include <memory>

#include <glm/glm.hpp>

#include "luawrapperfunction.h"


struct lua_State;

class LuaWrapper
{
public:
    LuaWrapper();
    ~LuaWrapper();

    void loadScript(const std::string & script);
    void removeScript(const std::string & script);
    void reloadScripts();

    static void reloadAll();


protected:
    void luaError();
    void pushFunc(const std::string & func) const;
    void callFunc(const int numArgs, const int numRet);

    void popStack(const int index);

    template <typename T, typename... Ts>
    void push(const T value, const Ts... values) const
    {
        push(value);
        push(values...);
    };

    void push() const;
    void push(const std::string & value) const;
    void push(const char * value) const;
    void push(const int8_t value) const;
    void push(const uint8_t value) const;
    void push(const int16_t value) const;
    void push(const uint16_t value) const;
    void push(const int32_t value) const;
    void push(const uint32_t value) const;
    void push(const int64_t value) const;
    void push(const uint64_t value) const;
    void push(const float value) const;
    void push(const double value) const;
    void push(const bool value) const;
    void push(const glm::vec3 & value) const;

    template <typename T> T fetch(const int index) const;

    template <size_t, typename... Ts>
    struct _pop
    {
        typedef std::tuple<Ts...> type;

        template <typename T>
        static std::tuple<T> worker(const LuaWrapper &instance, const int index)
        {
            return std::make_tuple(instance.fetch<T>(index));
        }

        template <typename T1, typename T2, typename... Rest>
        static std::tuple<T1, T2, Rest...> worker(const LuaWrapper &instance, const int index)
        {
            std::tuple<T1> head = std::make_tuple(instance.fetch<T1>(index));
            return std::tuple_cat(head, worker<T2, Rest...>(instance, index + 1));
        }

        static type apply(LuaWrapper &instance)
        {
            type ret = worker<Ts...>(instance, 1);
            instance.popStack(sizeof...(Ts));
            return ret;
        }
    };

    template <typename... Ts>
    struct _pop<0, Ts...>
    {
        typedef void type;
        static type apply(LuaWrapper & /*instance*/){}
    };

    template <typename T>
    struct _pop<1, T>
    {
        typedef T type;
        static T apply(LuaWrapper &instance)
        {
            // fetch the top element (negative indices count from the top)
            T ret  = instance.fetch<T>(-1);

            instance.popStack(1);
            return ret;
        }
    };

    template <typename... T>
    typename _pop<sizeof...(T), T...>::type pop()
    {
        return _pop<sizeof...(T), T...>::apply(*this);
    }


public:
    template <typename... Ret, typename... Args>
    typename _pop<sizeof...(Ret), Ret...>::type call(const std::string &fun, const Args&... args)
    {
        pushFunc(fun.c_str());
        push(args...);

        const int numArgs = sizeof...(Args);
        const int numRet = sizeof...(Ret);

        callFunc(numArgs, numRet);

        return pop<Ret...>();
    }

    template <typename Return, typename... Args>
    void Register(const std::string & name, std::function<Return(Args...)> function)
    {
        auto tmp = std::unique_ptr<BaseLuaFunction>(new LuaFunction<1, Return, Args...>{m_state, name, function});
        m_functions.insert(std::make_pair(name, std::move(tmp)));
    }

    template <typename Return, typename... Args>
    void Register(const std::string & name, Return (*function)(Args...))
    {
        auto tmp = std::unique_ptr<BaseLuaFunction>(new LuaFunction<1, Return, Args...>{m_state, name, function});
        m_functions.insert(std::make_pair(name, std::move(tmp)));
    }

    template <typename... Return, typename... Args>
    void Register(const std::string & name, std::function<std::tuple<Return...>(Args...)> function)
    {
        const int num_return = sizeof...(Return);
        auto tmp = std::unique_ptr<BaseLuaFunction>(new LuaFunction<num_return, std::tuple<Return...>, Args...>{m_state, name, function});
        m_functions.insert(std::make_pair(name, std::move(tmp)));
    }

    template <typename... Return, typename... Args>
    void Register(const std::string & name, std::tuple<Return...> (*function)(Args...))
    {
        const int num_return = sizeof...(Return);
        auto tmp = std::unique_ptr<BaseLuaFunction>(new LuaFunction<num_return, std::tuple<Return...>, Args...>{m_state, name, function});
        m_functions.insert(std::make_pair(name, std::move(tmp)));
    }

    void Unregister(const std::string &name) {
        auto it = m_functions.find(name);
        if (it != m_functions.end()) m_functions.erase(it);
    }


protected:
    lua_State * m_state;

    std::vector<std::string> m_scripts;
    int m_err;

    std::map<std::string, std::unique_ptr<BaseLuaFunction>> m_functions;

    static std::list<LuaWrapper *> s_instances;


public:
    void operator=(LuaWrapper &) = delete;
};
