#pragma once

#include "voxel/specialvoxel.h"


class CrucialVoxel: public SpecialVoxel {
public:
    CrucialVoxel(const glm::ivec3& gridCell, int index);

    virtual void addToObject(WorldObject* worldObject) override;

    virtual void onRemoval() override;
};

