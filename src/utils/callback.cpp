#include "callback.h"

#include <cassert>

#include "callbackimpl.h"


Callback::~Callback() = default;

bool Callback::dead() const {
    return m_impl->dead();
}

void Callback::call() {
    m_impl->call();
}

