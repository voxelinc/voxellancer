#include "voxel.h"

#include <iostream>
#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "voxelcluster.h"
#include "worldobject/worldobject.h"
#include "voxel/voxeltreenode.h"
#include "voxeleffect/voxelexplosiongenerator.h"


Voxel::Voxel(const glm::ivec3& gridCell, int color, float normalizedMass, float hp):
    m_gridCell(gridCell),
    m_voxelTreeNode(nullptr),
    m_color(color),
    m_normalizedMass(normalizedMass),
    m_hp(hp)
{
    assert(m_normalizedMass > 0.0f);

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

const glm::ivec3& Voxel::gridCell() const {
    return m_gridCell;
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

float Voxel::normalizedMass() const {
    return m_normalizedMass;
}

void Voxel::onRemoval() {

}

void Voxel::onDestruction() {
    assert(m_voxelTreeNode);

    WorldObject* worldObject = m_voxelTreeNode->voxelTree()->worldObject();

    if (m_voxelTreeNode && worldObject) {
        VoxelExplosionGenerator generator;
        generator.setOrientation(worldObject->transform().orientation());
        generator.setPosition(worldObject->transform().position()
            + worldObject->transform().orientation() * (-worldObject->transform().center() + glm::vec3(m_gridCell)));
        generator.setScale(worldObject->transform().scale());
        generator.setColor(m_color);
        generator.setForce(0.8f);
        generator.setLifetime(Property<float>("vfx.debrisLifetime"), 0.3f);
        generator.spawn();
    }
}

