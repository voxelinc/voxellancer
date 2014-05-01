#pragma once

#include <memory>


template<typename T>
class Component {
public:
    template<typename... Args>
    Component(Args... args);

    T& get();

    operator T&();

    T* operator->();

    T& operator*();


protected:
    std::unique_ptr<T> m_value;
};


#include "component.inl"
