#pragma once


template<typename BaseT, typename DerivedT>
DerivedT *throwing_dynamic_cast<DerivedT*>(BaseT *basePtr);

template<typename BaseT, typename DerivedT>
const DerivedT *throwing_dynamic_cast<DerivedT*>(const BaseT *basePtr);


#include "rtti.inl"
