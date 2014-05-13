#include "functionaluniverseelement.h"

#include "universe.h"
#include "sector.h"


FunctionalUniverseElement::FunctionalUniverseElement() = default;

FunctionalUniverseElement::~FunctionalUniverseElement() = default;

void FunctionalUniverseElement::spawn() {
    assert(universe());

    if (sector()) {
        sector()->addElement(this);
    } else {
        universe()->addElement(this);
    }
}

