#include "handle.h"

#include <assert.h>

#include "handleimpl.h"


template<class T>
Handle<T>::Handle(T* object) :
    m_impl(std::make_shared<HandleImpl<T>>(object))
{
}

template<class T>
T* Handle<T>::get() {
    return m_impl->get();
}

template<class T>
const T* Handle<T>::get() const {
    return m_impl->get();
}

template<class T>
T* Handle<T>::operator->() {
    return m_impl->get();
}

template<class T>
const T* Handle<T>::operator->() const {
    return m_impl->get();
}

template<class T>
T* Handle<T>::operator*() {
    return m_impl->get();
}

template<class T>
const T* Handle<T>::operator*() const {
    return m_impl->get();
}

template<class T>
bool Handle<T>::valid() const {
    return m_impl->valid();
}

template<class T>
void Handle<T>::invalidate() {
    m_impl->invalidate();
}

