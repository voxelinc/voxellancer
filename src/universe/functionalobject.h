#pragma once

#include "gameobject.h"


class FunctionalObject : public GameObject {
public:
    FunctionalObject();
    virtual ~FunctionalObject();


protected:
    virtual void doSpawn() override;

    virtual void doUnspawn() override;

    virtual void doWarp(Sector& sector) override;
};

