#pragma once


template<typename Target> class ReferenceHandle;
template<typename Target> class Referencor;

template<typename Target>
class Referenceable {
public:
    virtual ~Referenceable();

    ReferenceHandle<Target>* createHandle(Referencor<Target>& referencor);
    void invalidateHandles();


protected:
    std::list<ReferenceHandle<Target>*> m_referenceHandles;

    friend class Referencor<Target>;

    void referencorInvalid(ReferenceHandle<Target>* referenceHandle);
};

#include "referenceable.inl"
