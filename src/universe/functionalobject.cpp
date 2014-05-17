#include "functionalgameobject.h"

#include <cassert>

#include "universe.h"
#include "sector.h"


FunctionalObject::FunctionalObject() = default;

FunctionalObject::~FunctionalObject() = default;

void FunctionalObject::spawn() {
    assert(universe());

    if (sector()) {
        sector()->addElement(this);
    } else {
        universe()->addElement(this);
    }
}

