#pragma once

#include "worldobject.h"



class Split : public WorldObject {
public:
    Split(const WorldTransform& transform);

    virtual void finishInitialization() override;
};
