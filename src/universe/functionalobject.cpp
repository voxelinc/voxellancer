#include "functionalobject.h"

#include <cassert>

#include "universe.h"
#include "sector.h"


FunctionalObject::FunctionalObject() = default;

FunctionalObject::~FunctionalObject() = default;

bool FunctionalObject::doSpawn() {
    assert(universe());

    if (sector()) {
        sector()->addFunctionalObject(this);
    } else {
        universe()->addFunctionalObject(this);
    }

    return true;
}

