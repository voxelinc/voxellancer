#pragma once

#include "worldobject.h"



class Split : public WorldObject {
public:
    Split(const WorldTransform& transform, CollisionFilterClass collisionFilterClass);

    virtual void finishInitialization() override;
};
