#include "physicalgameobject.h"

#include <cassert>


void VoxelObject::spawn() {
    assert(universe());
    assert(sector());

    sector()->addElement(this);
}

