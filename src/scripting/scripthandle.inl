#pragma once


template<typename T>
ScriptHandle<T>::ScriptHandle(T* scriptable):
    m_handle(scriptable->handle())
{
}

template<typename T>
bool ScriptHandle<T>::valid() const {
    return m_handle.valid();
}

template<typename T>
void ScriptHandle<T>::invalidate() {
    m_handle.invalidate();
}

template<typename T>
Scriptable* ScriptHandle<T>::scriptable() {
    return m_handle.get();
}

