#include "handle.h"

#include <assert.h>

#include "handleimpl.h"


template<typename T>
Handle<T>::Handle(T* object):
    m_impl(std::make_shared<HandleImpl<T>>(object)),
    m_root(true)
{
}

template<typename T>
Handle<T>::Handle(const Handle<T>& other):
    m_impl(other.m_impl),
    m_root(false)
{
}

template<typename T>
Handle<T>::Handle(const Handle<T>&& rother):
    m_impl(rother.m_impl),
    m_root(false)
{
}

template<typename T>
Handle<T>::~Handle()
{
    if (m_root) {
        invalidate();
    }
}

template<typename T>
T* Handle<T>::get() {
    return m_impl->get();
}

template<typename T>
const T* Handle<T>::get() const {
    return m_impl->get();
}

template<typename T>
T* Handle<T>::operator->() {
    return m_impl->get();
}

template<typename T>
const T* Handle<T>::operator->() const {
    return m_impl->get();
}

template<typename T>
T* Handle<T>::operator*() {
    return m_impl->get();
}

template<typename T>
const T* Handle<T>::operator*() const {
    return m_impl->get();
}

template<typename T>
Handle<T>& Handle<T>::operator=(const Handle<T>& other) {
    if (this == &other) {
        return *this;
    }

    if (m_root) {
        invalidate();
    }

    m_impl = other.m_impl;
    m_root = false;
}

template<typename T>
Handle<T>& Handle<T>::operator=(const Handle<T>&& rother) {
    if (m_root) {
        invalidate();
    }

    m_impl = rother.m_impl;
    m_root = false;
}

template<typename T>
bool Handle<T>::root() const {
    return m_root;
}

template<typename T>
bool Handle<T>::valid() const {
    return m_impl->valid();
}

template<typename T>
void Handle<T>::invalidate() {
    assert(m_root);
    m_impl->invalidate();
}

