#pragma once

#include <list>


template<typename Target> class ReferenceHandle;
template<typename Target> class Referenceable;

template<typename Target>
class Referencor {
public:
    ~Referencor();

    void holdReferenceHandle(ReferenceHandle<Target>* referenceHandle);
    void discardHandle(ReferenceHandle<Target>* referenceHandle);
    void invalidateHandles();

    virtual void referenceInvalid(const Target* target) = 0;


protected:
    std::list<ReferenceHandle<Target>*> m_referenceHandles;

    friend class Referenceable<Target>;

    /* To be called by Referenceable */
    void referenceableInvalidatedHandle(ReferenceHandle<Target>* referenceHandle);
};


#include "referencor.inl"
