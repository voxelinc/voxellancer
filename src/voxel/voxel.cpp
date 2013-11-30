#include "voxel.h"

#include <cassert>

#include "voxelcluster.h"


Voxel::Voxel():
    m_voxelCluster(nullptr),
    m_gridCell(0, 0, 0),
    m_color(1, 0, 1)
{
}

Voxel::Voxel(cvec3 gridCell, cvec3 color):
    m_voxelCluster(nullptr),
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

void Voxel::setVoxelCluster(VoxelCluster *cluster){
    m_voxelCluster = cluster;
}

void Voxel::addToCluster(VoxelCluster *cluster){
    cluster->addVoxel(this);
}

const cvec3 &Voxel::gridCell() const {
    return m_gridCell;
}

//void Voxel::setGridCell(const cvec3 &cell) {
//    m_gridCell = cell;
//}

const cvec3 &Voxel::color() const {
    return m_color;
}

//void Voxel::setColor(const cvec3 &color) {
//    m_color = color;
//}

