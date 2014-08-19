#pragma once

#include "handleimpl.h"


template<typename T>
Handle<T>::Handle():
    m_impl(new HandleImpl(nullptr)),
    m_referenced(nullptr)
{
}

template<typename T>
Handle<T>::Handle(const std::shared_ptr<HandleImpl>& impl):
    m_impl(impl ? impl : std::make_shared<HandleImpl>(nullptr)),
    m_referenced(impl ? static_cast<T*>(impl->owner()) : nullptr)
{
}

template<typename T>
T* Handle<T>::get() {
    return m_impl->valid() ? m_referenced : nullptr;
}

template<typename T>
const T* Handle<T>::get() const {
    return m_impl->valid() ? m_referenced : nullptr;
}

template<typename T>
bool Handle<T>::valid() const {
    return m_impl->valid();
}

template<typename T>
Handle<T>::operator bool() const {
    return m_impl->valid();
}

template<typename T>
T* Handle<T>::operator->() {
    return get();
}

template<typename T>
const T* Handle<T>::operator->() const {
    return get();
}

template<typename T>
T* Handle<T>::operator*() {
    return get();
}

template<typename T>
const T* Handle<T>::operator*() const {
    return get();
}

template<typename T>
Handle<T>& Handle<T>::operator=(T& other) {
    operator=(makeHandle(other));
    return *this;
}

template<typename T>
bool Handle<T>::operator==(const T* other) const {
    return m_referenced == other;
}

template<typename T>
bool Handle<T>::operator==(const T& other) const {
    return m_referenced == &other;
}

