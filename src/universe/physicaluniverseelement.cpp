#include "physicaluniverseelement.h"

#include <cassert>


void PhysicalUniverseElement::spawn() {
    assert(universe());
    assert(sector());

    sector()->addElement(this);
}

