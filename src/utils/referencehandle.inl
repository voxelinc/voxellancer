#pragma once

#include "referencor.h"


template<typename Target>
ReferenceHandle<Target>::ReferenceHandle(Target& reference, Referencor<Target>& holder):
    m_reference(reference),
    m_holder(holder)
{

}

template<typename Target>
Target& ReferenceHandle<Target>::reference() {
    return m_reference;
}

template<typename Target>
const Target& ReferenceHandle<Target>::reference() const {
    return m_reference;
}

template<typename Target>
Referencor<Target>& ReferenceHandle<Target>::holder() {
    return m_holder;
}

template<typename Target>
const Referencor<Target>& ReferenceHandle<Target>::holder() const {
    return m_holder;
}

template<typename Target>
ReferenceHandle<Target>::operator Target&() {
    return m_reference;
}

template<typename Target>
ReferenceHandle<Target>::operator const Target&() const {
    return m_reference;
}

