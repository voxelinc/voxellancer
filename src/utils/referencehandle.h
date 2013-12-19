#pragma once


template<typename Target> class Referencor;

template<typename Target>
class ReferenceHandle {
public:
    ReferenceHandle(Target& reference, Referencor<Target>& referencor);

    Target& reference();
    const Target& reference() const;

    Referencor<Target>& referencor();
    const Referencor<Target>& referencor() const;

    operator Target&();
    operator const Target&() const;


protected:
    Target& m_reference;
    Referencor<Target>& m_holder;
};

#include "referencehandle.inl"
