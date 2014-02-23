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

    void start();


protected:
    std::unique_ptr<LuaWrapper> m_lua;
    bool m_started;
};

