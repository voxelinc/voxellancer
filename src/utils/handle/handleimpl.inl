
#include "handleimpl.h"

#include <assert.h>


template<typename T>
HandleImpl<T>::HandleImpl(T* object) :
    m_object(object)
{
}

template<typename T>
T* HandleImpl<T>::get() {
    return m_object;
}

template<typename T>
bool HandleImpl<T>::valid() const {
    return m_object != nullptr;
}

template<typename T>
void HandleImpl<T>::invalidate() {
    m_object = nullptr;
}

