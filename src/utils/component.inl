#pragma once


template<typename T>
template<typename... Args>
Component<T>::Component(Args&... args):
    m_value(new T(args...))
{
}

template<typename T>
T& Component<T>::get() {
    return *m_value;
}

template<typename T>
Component<T>::operator T&() {
    return *m_value;
}

template<typename T>
T* Component<T>::operator->() {
    return m_value.get();
}

template<typename T>
T& Component<T>::operator*() {
    return *m_value;
}

