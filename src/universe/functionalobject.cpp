#include "functionalgameobject.h"

#include <cassert>

#include "universe.h"
#include "sector.h"


FunctionalObject::FunctionalObject() = default;

FunctionalObject::~FunctionalObject() = default;

void FunctionalObject::spawn() {
    assert(universe());

    if (sector()) {
        sector()->addFunctionalObject(this);
    } else {
        universe()->addFunctionalObject(this);
    }
}

