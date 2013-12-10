#include "voxel.h"

#include <iostream>
#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "voxelcluster.h"
#include "worldobject/worldobject.h"



Voxel::Voxel(const glm::ivec3& gridCell, int color, float mass, float hp):
    m_gridCell(gridCell),
    m_color(color),
    m_mass(mass),
    m_hp(hp)
{
    assert( gridCell.x >= 0 && gridCell.x < 256 &&
            gridCell.y >= 0 && gridCell.y < 256 &&
            gridCell.z >= 0 && gridCell.z < 256);
}

Voxel::~Voxel() {
}


void Voxel::addToCluster(VoxelCluster *cluster){
    cluster->addVoxel(this);
}

void Voxel::addToObject(WorldObject *object){
    object->addVoxel(this);
}

const glm::ivec3 &Voxel::gridCell() const {
    return m_gridCell;
}

int Voxel::color() const {
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

}

