#pragma once

#include "referencehandle.h"


template<typename Target>
Referencor<Target>::~Referencor() {
    for(ReferenceHandle<Target>* referenceHandle : m_referenceHandles) {
        referenceHandle->reference().holderDestroyed(referenceHandle);
        delete referenceHandle;
    }
}

template<typename Target>
void Referencor<Target>::holdReferenceHandle(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.push_back(referenceHandle);
}

template<typename Target>
void Referencor<Target>::handleDestroyed(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.remove(referenceHandle);
    delete referenceHandle;
}

