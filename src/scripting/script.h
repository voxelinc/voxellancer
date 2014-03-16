#pragma once

#include <memory>
#include <string>


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

    const std::string& debugStatus();
    int apiSetDebugStatus(const std::string& string);

protected:
    std::unique_ptr<LuaWrapper> m_lua;
    bool m_started;
    std::string m_debugStatus;
};
