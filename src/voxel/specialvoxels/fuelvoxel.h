#pragma once

#include "voxel/specialvoxel.h"


class FuelVoxel: public SpecialVoxel {
public:
    FuelVoxel(const glm::ivec3& gridCell, int index);

    virtual void addToObject(WorldObject* worldObject) override;

    virtual float damageForwardingDestructionDamage() override;

    virtual void onDestruction() override;

    virtual FuelVoxel* clone() const override;
};

