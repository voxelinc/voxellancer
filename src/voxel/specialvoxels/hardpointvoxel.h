#pragma once

#include "display/rendering/visuals.h"

#include "voxel/specialvoxel.h"


class Hardpoint;

class HardpointVoxel: public SpecialVoxel {
public:
    HardpointVoxel(const glm::ivec3& gridCell, int index);
    HardpointVoxel(const HardpointVoxel& other);

    virtual Visuals visuals() const override;

    virtual void addToObject(WorldObject* object) override;

    virtual void onRemoval() override;

    virtual HardpointVoxel* clone() const override;


protected:
    std::shared_ptr<Hardpoint> m_hardpoint;
};

