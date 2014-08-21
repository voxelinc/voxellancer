#pragma once

#include "voxel/specialvoxel.h"


class CockpitVoxel: public SpecialVoxel {
public:
    CockpitVoxel(const glm::ivec3& cell, int index);

    virtual void addToObject(WorldObject* object) override;

    virtual void onRemoval() override;
    virtual void onDestruction() override;
};

