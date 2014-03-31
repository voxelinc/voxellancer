#pragma once


class LuaWrapper;
class ScriptEngine;
class GamePlay;
class GamePlayScript;

typedef int apikey;

class Bindings {
public:
    Bindings(GamePlayScript& gamePlayScript);

    virtual void bind() = 0;


protected:
    LuaWrapper& m_lua;
    GamePlayScript& m_script;
    ScriptEngine& m_scriptEngine;
};

