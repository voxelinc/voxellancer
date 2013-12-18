#pragma once

#include <list>


template<typename Target> class ReferenceHandle;

template<typename Target>
class Referencor {
public:
    ~Referencor();

    void holdReferenceHandle(ReferenceHandle<Target>* referenceHandle);
    void handleDestroyed(ReferenceHandle<Target>* referenceHandle);
    virtual void referenceDestroyed(const Target* target) = 0;


protected:
    std::list<ReferenceHandle<Target>*> m_referenceHandles;
};


#include "referencor.inl"
