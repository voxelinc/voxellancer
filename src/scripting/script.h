#pragma once

#include <memory>
#include <string>
#include <vector>


class Bindings;
class LuaWrapper;

/*
    Handle to a lua script
*/
class Script {
public:
    Script();
    ~Script();

    bool started() const;

    virtual void load(const std::string& path);
    virtual void loadString(const std::string& script);

    void start();

    void update(float deltaSec);

    const std::string& debugStatus();


protected:
    std::unique_ptr<LuaWrapper> m_lua;
    bool m_started;
    std::string m_debugStatus;
    std::vector<std::unique_ptr<Bindings>> m_bindings;


    void addBindings(Bindings* bindings);

    int apiSetDebugStatus(const std::string& string);
};


