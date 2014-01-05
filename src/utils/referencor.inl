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
void Referencor<Target>::discardHandle(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.remove(referenceHandle);
    referenceHandle->reference().referencorInvalidatedHandle(referenceHandle);
    delete referenceHandle;
}

template<typename Target>
void Referencor<Target>::invalidateHandles() {
    for(ReferenceHandle<Target>* referenceHandle : m_referenceHandles) {
        referenceHandle->reference().referencorInvalidatedHandle(referenceHandle);
        delete referenceHandle;
    }
}

template<typename Target>
void Referencor<Target>::referenceableInvalidatedHandle(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.remove(referenceHandle);
    delete referenceHandle;
}

