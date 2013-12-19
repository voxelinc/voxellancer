#pragma once

#include "referencehandle.h"


template<typename Target>
Referencor<Target>::~Referencor() {
    invalidateHandles();
}

template<typename Target>
void Referencor<Target>::holdReferenceHandle(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.push_back(referenceHandle);
}

template<typename Target>
void Referencor<Target>::invalidateHandles() {
    for(ReferenceHandle<Target>* referenceHandle : m_referenceHandles) {
        referenceHandle->reference().referencorInvalid(referenceHandle);
        delete referenceHandle;
    }
}

template<typename Target>
void Referencor<Target>::handleInvalid(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.remove(referenceHandle);
    delete referenceHandle;
}

