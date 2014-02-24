#pragma once

#include "voxel/specialvoxel.h"


class CrucialVoxel: public SpecialVoxel {
public:
    CrucialVoxel(const glm::ivec3& gridCell, int index);

    virtual void addToObject(WorldObject* worldObject);

    virtual void onRemoval();
    virtual void onDestruction(const WorldObject* owner);
};
