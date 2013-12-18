#pragma once

#include <cassert>

#include "referencehandle.h"
#include "referencor.h"


template<typename Target>
Referenceable<Target>::~Referenceable() {
    for(ReferenceHandle<Target>* referenceHandle : m_referenceHandles) {
        referenceHandle->holder().handleDestroyed(referenceHandle);
        referenceHandle->holder().referenceDestroyed(&referenceHandle->reference());
    }
}

template<typename Target>
ReferenceHandle<Target>* Referenceable<Target>::createHandle(Referencor<Target>& holder) {
    Target* target = dynamic_cast<Target*>(this);
    assert(target != nullptr);

    ReferenceHandle<Target>* referenceHandle = new ReferenceHandle<Target>(*target, holder);
    m_referenceHandles.push_back(referenceHandle);
    holder.holdReferenceHandle(referenceHandle);

    return referenceHandle;
}

template<typename Target>
void Referenceable<Target>::holderDestroyed(ReferenceHandle<Target>* referenceHandle) {
    m_referenceHandles.remove(referenceHandle);
}


