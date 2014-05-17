#pragma once

#include "gameobject.h"


class VoxelObject {
public:
    VoxelObject();
    virtual ~VoxelObject();

    virtual void spawn() override;
};

