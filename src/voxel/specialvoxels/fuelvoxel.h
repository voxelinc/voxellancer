#pragma once

#include "voxel/specialvoxel.h"


class FuelVoxel: public SpecialVoxel {
public:
    FuelVoxel(const glm::ivec3& cell, int index);

    virtual void addToObject(WorldObject* worldObject) override;

    virtual float damageForwardingDestructionDamage() override;

    virtual void onRemoval() override;
    virtual void onDestruction() override;
};

