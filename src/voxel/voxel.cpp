#include "voxel.h"

#include <cassert>

#include "voxelcluster.h"


Voxel::Voxel(VoxelCluster *voxelCluster):
    m_voxelCluster(voxelCluster),
    m_gridCell(0, 0, 0),
    m_color(1, 0, 1)
{
}

Voxel::Voxel(cvec3 gridCell, ucvec3 color, VoxelCluster *voxelCluster):
    m_voxelCluster(voxelCluster),
    m_gridCell(gridCell),
    m_color(color)
{
    assert(gridCell.x >= 0 && gridCell.y >= 0 && gridCell.z >= 0);
}

Voxel::~Voxel() {

}

VoxelCluster *Voxel::voxelCluster() {
    return m_voxelCluster;
}

const VoxelCluster *Voxel::voxelCluster() const {
    return m_voxelCluster;
}

const cvec3 &Voxel::gridCell() const {
    return m_gridCell;
}

void Voxel::setGridCell(const cvec3 &cell) {
    m_gridCell = cell;
}

const ucvec3 &Voxel::color() const {
    return m_color;
}

void Voxel::setColor(const ucvec3 &color) {
    m_color = color;
}

