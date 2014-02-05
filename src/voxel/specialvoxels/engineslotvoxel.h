#pragma once

#include "voxel/specialvoxel.h"


class EngineSlot;

class EngineSlotVoxel: public SpecialVoxel {
public:
    EngineSlotVoxel(const glm::ivec3& gridCell, int index);

    virtual Visuals visuals() const override;

    virtual void addToObject(WorldObject* worldObject) override;

    virtual void onRemoval() override;
    virtual void onDestruction() override;



protected:
    EngineSlot* m_engineSlot;
};

