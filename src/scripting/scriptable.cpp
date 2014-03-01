#include "scriptable.h"

#include <cassert>


Scriptable::Scriptable():
    m_key(-1)
{

}

int Scriptable::scriptKey() const {
    return m_key;
}

void Scriptable::setScriptKey(int key) {
    assert(m_key < 0);
    m_key = key;
}
