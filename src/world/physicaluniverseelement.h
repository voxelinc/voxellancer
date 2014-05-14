#pragma once

#include "universeelement.h"


class PhysicalUniverseElement {
public:
    PhysicalUniverseElement();
    virtual ~PhysicalUniverseElement();

    virtual void spawn() override;
};
