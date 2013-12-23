#include "voxel.h"

#include <iostream>
#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "voxelcluster.h"
#include "worldobject/worldobject.h"



Voxel::Voxel(const glm::ivec3& gridCell, int color, float normalizedMass, float hp):
    m_gridCell(gridCell),
    m_voxelTreeNode(nullptr),
    m_color(color),
    m_normalizedMass(normalizedMass),
    m_hp(hp)
{
    assert( gridCell.x >= 0 && gridCell.x < 256 &&
            gridCell.y >= 0 && gridCell.y < 256 &&
            gridCell.z >= 0 && gridCell.z < 256);
}

Voxel::Voxel(const Voxel& other):
    Voxel(other.gridCell(), other.color(), other.normalizedMass(), other.hp())
{
}

Voxel::~Voxel() {
}


void Voxel::addToCluster(VoxelCluster *cluster) {
    cluster->addVoxel(this);
}

void Voxel::addToObject(WorldObject *object) {
    object->addVoxel(this);
}

const glm::ivec3 &Voxel::gridCell() const {
    return m_gridCell;
}

VoxelTreeNode *Voxel::voxelTreeNode() {
    return m_voxelTreeNode;
}

void Voxel::setVoxelTreeNode(VoxelTreeNode* voxelTreeNode) {
    m_voxelTreeNode = voxelTreeNode;
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

float Voxel::normalizedMass() const {
    return m_normalizedMass;
}

void Voxel::onRemoval() {

}

void Voxel::onDestruction() {

}

