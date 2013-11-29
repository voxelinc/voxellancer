#include "physicalVoxelimpact.h"

PhysicalPhysicalVoxelImpact::PhysicalPhysicalVoxelImpact(PhysicalVoxel *physicalVoxel, const Impact &impact):
    m_physicalVoxel(physicalVoxel),
    m_impact(impact)
{
}

PhysicalVoxel *PhysicalPhysicalVoxelImpact::physicalVoxel() {
    return m_physicalVoxel;
}

const PhysicalVoxel *PhysicalPhysicalVoxelImpact::physicalVoxel() const {
    return m_physicalVoxel;
}

const Impact &PhysicalPhysicalVoxelImpact::impact() const {
    return m_impact;
}

void PhysicalPhysicalVoxelImpact::addImpact(const Impact &impact) {
    m_impact.add(impact);
}

