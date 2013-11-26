#include "voxelimpact.h"

#include <assert.h>


VoxelImpact::VoxelImpact(Voxel *voxel, const Impact &impact):
    m_voxel(voxel),
    m_impact(impact)
{
    assert(voxel != nullptr);
}

Voxel *VoxelImpact::voxel() {
    return m_voxel;
}

const Voxel *VoxelImpact::voxel() const {
    return m_voxel;
}

const Impact &VoxelImpact::impact() const {
    return m_impact;
}

void VoxelImpact::setImpact(const Impact &impact) {
    m_impact = impact;
}

void VoxelImpact::addImpact(const Impact &impact) {
    m_impact.add(impact);
}

