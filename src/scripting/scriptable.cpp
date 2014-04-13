#include "scriptable.h"

#include <cassert>

#include "world/world.h"
#include "scriptengine.h"


Scriptable::Scriptable():
    m_key(INVALID_KEY),
    m_local(false)
{

}

Scriptable::~Scriptable() = default;

int Scriptable::scriptKey() const {
    return m_key;
}

void Scriptable::setScriptKey(int key) {
    assert(m_key == INVALID_KEY || key == INVALID_KEY);
    m_key = key;
}

bool Scriptable::isScriptLocal() const {
    return m_local;
}

void Scriptable::setScriptLocal(bool local) {
    m_local = local;
}
