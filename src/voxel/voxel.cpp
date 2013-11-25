#include "voxel.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "voxelcluster.h"


Voxel::Voxel(VoxelCluster *voxelCluster):
    m_voxelCluster(voxelCluster),
    m_gridCell(0, 0, 0),
    m_color(1, 0, 1),
    m_hp(1)
{
}

Voxel::Voxel(cvec3 gridCell, cvec3 color, VoxelCluster *voxelCluster):
    m_voxelCluster(voxelCluster),
    m_gridCell(gridCell),
    m_color(color),
    m_hp(1)
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


const cvec3 &Voxel::color() const {
    return m_color;
}

void Voxel::setColor(const cvec3 &color) {
    m_color = color;
}

float Voxel::hp() const {
    return m_hp;
}

void Voxel::applyDamage(float deltaHp) {
    m_hp = std::max(m_hp - deltaHp, 0.0f);
}

void Voxel::onDestruction() {
    std::cout << "I'm voxel " << this << " and I'm going now. So long and thx 4 all the fish!" << std::endl;
}

glm::vec3 Voxel::position() const {
    glm::vec3 cell = static_cast<glm::vec3>(m_gridCell);
    return glm::vec3(m_voxelCluster->transform().matrix() * glm::vec4(cell, 1.0f));
}
