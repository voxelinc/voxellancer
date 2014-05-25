#include "functionalobject.h"

#include <cassert>

#include "universe.h"
#include "sector.h"


FunctionalObject::FunctionalObject() = default;

FunctionalObject::~FunctionalObject() = default;

void FunctionalObject::doSpawn() {
    if (sector()) {
        sector()->addFunctionalObject(this);
    } else {
        universe()->addFunctionalObject(this);
    }
}

void FunctionalObject::doUnspawn() {
    if (sector()) {
        sector()->removeFunctionalObject(this);
    } else {
        universe()->removeFunctionalObject(this);
    }
}

void FunctionalObject::doWarp(Sector& sector) {
    abort();
}

