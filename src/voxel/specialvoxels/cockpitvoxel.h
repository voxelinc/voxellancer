#pragma once

#include "voxel/specialvoxel.h"


class CockpitVoxel: public SpecialVoxel {
public:
    CockpitVoxel(const glm::ivec3& gridCell, int index);

    virtual void addToObject(WorldObject* object) override;

    virtual void onRemoval() override;
};

