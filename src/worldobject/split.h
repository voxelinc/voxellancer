#pragma once

#include "worldobject.h"



class Split : public WorldObject {
public:
    Split(const Transform& transform, CollisionFilterClass collisionFilterClass);
};
