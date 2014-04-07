#include "callback.h"

#include <cassert>

#include "callbackimpl.h"


Callback::~Callback() = default;

void Callback::call() {
    assert(m_impl.get());
    m_impl.get()->call();
}
