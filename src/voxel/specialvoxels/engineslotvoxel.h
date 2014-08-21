#pragma once

#include <memory>

#include "voxel/specialvoxel.h"


class EngineSlot;

class EngineSlotVoxel: public SpecialVoxel {
public:
    EngineSlotVoxel(const glm::ivec3& gridCell, int index);
    EngineSlotVoxel(const EngineSlotVoxel& other);

    virtual Visuals visuals() const override;

    virtual void addToObject(WorldObject* worldObject) override;

    virtual void onRemoval() override;

    virtual EngineSlotVoxel* clone() const override;


protected:
    std::shared_ptr<EngineSlot> m_engineSlot;
};

