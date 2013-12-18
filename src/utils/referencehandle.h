#pragma once


template<typename Target> class Referencor;

template<typename Target>
class ReferenceHandle {
public:
    ReferenceHandle(Target& reference, Referencor<Target>& holder);

    Target& reference();
    const Target& reference() const;

    Referencor<Target>& holder();
    const Referencor<Target>& holder() const;

    operator Target&();
    operator const Target&() const;


protected:
    Target& m_reference;
    Referencor<Target>& m_holder;
};

#include "referencehandle.inl"
