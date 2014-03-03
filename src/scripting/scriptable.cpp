#include "scriptable.h"

#include <cassert>


Scriptable::Scriptable():
    m_key(-1)
{

}

Scriptable::~Scriptable() = default;

int Scriptable::scriptKey() const {
    return m_key;
}

void Scriptable::setScriptKey(int key) {
    assert(m_key < 0);
    m_key = key;
}

