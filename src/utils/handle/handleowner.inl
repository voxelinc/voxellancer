#pragma once

#include <cassert>


template<typename T>
Handle<T> HandleOwner::handle() {
    assert(m_impl->valid());

    HandleOwner* owner = m_impl->owner();

    T* derived = dynamic_cast<T*>(owner);
    assert(derived);

    return Handle<T>(m_impl);
}

template<typename T>
Handle<T> makeHandle(T* owner) {
    return owner ? owner->template handle<T>() : Handle<T>();
}

template<typename T>
Handle<T> makeHandle(T& owner) {
    return owner.template handle<T>();
}

