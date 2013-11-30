#include "voxel.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "voxelcluster.h"



Voxel::Voxel(const glm::ivec3& gridCell, const cvec3& color, float mass):
    m_gridCell(gridCell),
    m_color(color),
    m_hp(1),
    m_mass(mass)
{
    assert( gridCell.x >= 0 && gridCell.x < 256 &&
            gridCell.y >= 0 && gridCell.y < 256 &&
            gridCell.z >= 0 && gridCell.z < 256);
}

Voxel::~Voxel() {

}

Voxel *Voxel::clone() {
    Voxel *voxel = new Voxel(m_gridCell, m_color, m_mass);
    voxel->m_hp = m_hp;
    return voxel;
}

const glm::ivec3 &Voxel::gridCell() const {
    return m_gridCell;
}

const cvec3 &Voxel::color() const {
    return m_color;
}

float Voxel::hp() const {
    return m_hp;
}

void Voxel::applyDamage(float deltaHp) {
    m_hp = std::max(m_hp - deltaHp, 0.0f);
}

float Voxel::mass() const {
    return m_mass;
}

void Voxel::onDestruction() {
    std::cout << "I'm voxel " << this << " and I'm going now. So long and thx 4 all the fish!" << std::endl;
}

