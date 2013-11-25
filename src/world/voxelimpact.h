#pragma once

#include <glm/glm.hpp>

#include "voxel/voxel.h"
#include "physics/impact.h"


class VoxelImpact
{
public:
    VoxelImpact(Voxel *voxel, const Impact &impact = Impact(glm::vec3(0.0f, 0.0f, 0.0f)));

    Voxel *voxel();
    const Voxel *voxel() const;

    const Impact &impact() const;
    void setImpact(const Impact &impact);

    void addImpact(const Impact &impact);


protected:
    Voxel *m_voxel;
    Impact m_impact;
};

