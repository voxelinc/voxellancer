#pragma once

#include "universeelement.h"


class FunctionalUniverseElement {
public:
    FunctionalUniverseElement();
    virtual ~FunctionalUniverseElement();

    virtual void spawn() override;
};
