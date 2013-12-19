#pragma once

#include <cassert>

#include "referencehandle.h"
#include "referencor.h"


template<typename Target>
Referenceable<Target>::~Referenceable() {
    invalidateHandles();
}

template<typename Target>
ReferenceHandle<Target>* Referenceable<Target>::createHandle(Referencor<Target>& referencor) {
    Target* target = dynamic_cast<Target*>(this);
    assert(target != nullptr);

    ReferenceHandle<Target>* referenceHandle = new ReferenceHandle<Target>(*target, referencor);
    m_referenceHandles.push_back(referenceHandle);
    referencor.holdReferenceHandle(referenceHandle);

    return referenceHandle;
}

template<typename Target>
void Referenceable<Target>::invalidateHandles() {
    for(ReferenceHandle<Target>* referenceHandle : m_referenceHandles) {
        referenceHandle->referencor().referenceInvalid(&referenceHandle->reference());
        referenceHandle->referencor().referenceableInvalidatedHandle(referenceHandle);
    }
}

template<typename Target>
void Referenceable<Target>::referencorInvalidatedHandle(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.remove(referenceHandle);
}

