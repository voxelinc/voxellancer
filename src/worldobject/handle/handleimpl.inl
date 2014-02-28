
#include "handleimpl.h"

#include <assert.h>

template<class T>
HandleImpl<T>::HandleImpl(T* object) :
    m_object(object)
{
}

template<class T>
T* HandleImpl<T>::get() {
    return m_object;
}

template<class T>
const T* HandleImpl<T>::get() const {
    return m_object;
}

template<class T>
bool HandleImpl<T>::valid() const {
    return m_object != nullptr;
}

template<class T>
void HandleImpl<T>::invalidate() {
    m_object = nullptr;
}

