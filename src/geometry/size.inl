#pragma once

template<typename T>
Size<T>::Size():
    m_width(static_cast<T>(0)),
    m_height(static_cast<T>(0))
{
}

template<typename T>
Size<T>::Size(T width, T height):
    m_width(width),
    m_height(height)
{
}

template<typename T>
T Size<T>::width() const {
    return m_width;
}

template<typename T>
void Size<T>::setWidth(T width) {
    m_width = width;
}

template<typename T>
T Size<T>::height() const {
    return m_height;
}

template<typename T>
void Size<T>::setHeight(T height) {
    m_height = height;
}

