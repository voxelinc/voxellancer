#pragma once

#include "gameobject.h"


class FunctionalObject {
public:
    FunctionalObject();
    virtual ~FunctionalObject();

    virtual void spawn() override;
};

