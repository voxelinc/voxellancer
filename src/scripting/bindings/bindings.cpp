#include "bindings.h"
#include "scripting/gameplayscript.h"


Bindings::Bindings(GamePlayScript& script):
    m_script(script),
    m_lua(script.luaWrapper()),
    m_scriptEngine(script.scriptEngine())
{
}

