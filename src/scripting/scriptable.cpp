#include "scriptable.h"

#include <cassert>

#include "world/world.h"
#include "scriptengine.h"


Scriptable::Scriptable():
    m_key(INVALID_KEY)
{

}

Scriptable::~Scriptable() {
    if (m_key != INVALID_KEY) {
        World::instance()->scriptEngine().unregisterScriptable(this);
    }
}

int Scriptable::scriptKey() const {
    return m_key;
}

void Scriptable::setScriptKey(int key) {
    assert(m_key == INVALID_KEY || key == INVALID_KEY);
    m_key = key;
}

