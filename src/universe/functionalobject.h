#pragma once

#include "gameobject.h"


class FunctionalObject : public GameObject {
public:
    FunctionalObject();
    virtual ~FunctionalObject();


protected:
    virtual void doSpawn() override;
};

