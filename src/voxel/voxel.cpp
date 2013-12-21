#include "voxel.h"

#include <iostream>
#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "voxelcluster.h"
#include "worldobject/worldobject.h"



Voxel::Voxel(const glm::ivec3& gridCell, int color, float mass, float hp):
    m_gridCell(gridCell),
    m_voxelTreeNode(nullptr),
    m_color(color),
    m_mass(mass),
    m_hp(hp)
{
    assert( gridCell.x >= 0 && gridCell.x < 256 &&
            gridCell.y >= 0 && gridCell.y < 256 &&
            gridCell.z >= 0 && gridCell.z < 256);
}

Voxel::Voxel(const Voxel& other):
    Voxel(other.gridCell(), other.color(), other.mass(), other.hp())
{
}

Voxel::~Voxel() {
}

const glm::ivec3& Voxel::gridCell() const {
    return m_gridCell;
}

Sphere Voxel::normalizedSphere() const {
    Sphere result;
    result.setPosition(static_cast<glm::vec3>(m_gridCell));
    result.setRadius(0.5);
    return result;
}

void Voxel::addToCluster(VoxelCluster *cluster) {
    cluster->addVoxel(this);
}

void Voxel::addToObject(WorldObject *object) {
    object->addVoxel(this);
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

float Voxel::mass() const {
    return m_mass;
}

void Voxel::onRemoval() {

}

void Voxel::onDestruction() {

}

