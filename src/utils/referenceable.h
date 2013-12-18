#pragma once


template<typename Target> class ReferenceHandle;
template<typename Target> class Referencor;

template<typename Target>
class Referenceable {
public:
    virtual ~Referenceable();

    ReferenceHandle<Target>* createHandle(Referencor<Target>& referencor);
    void holderDestroyed(ReferenceHandle<Target>* referenceHandle);


protected:
    std::list<ReferenceHandle<Target>*> m_referenceHandles;
};

#include "referenceable.inl"
