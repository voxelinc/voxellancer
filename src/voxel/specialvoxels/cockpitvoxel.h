#pragma once

#include "voxel/specialvoxel.h"


class CockpitVoxel: public SpecialVoxel {
public:
    CockpitVoxel(const glm::ivec3& gridCell, int index);
    CockpitVoxel(const CockpitVoxel& other);

    virtual void addToObject(WorldObject* object) override;

    virtual CockpitVoxel* clone() const override;
};

