#include "voxel.h"

#include <iostream>
#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "voxelcluster.h"
#include "worldobject/worldobject.h"
#include "voxel/voxeltreenode.h"
#include "voxeleffect/voxeldebrisgenerator.h"
#include "voxeltree.h"


Property<float>* Voxel::s_defaultMass;
Property<float>* Voxel::s_defaultHp;

Voxel::Voxel(const glm::ivec3& gridCell, uint32_t color, float normalizedMass, float hp, float emissiveness):
    m_gridCell(gridCell),
    m_voxelTreeNode(nullptr),
    m_color(color),
    m_emissiveness(emissiveness),
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

glm::vec3 Voxel::position() const {
    assert(m_voxelTreeNode);
    return m_voxelTreeNode->voxelTree()->worldObject()->transform().applyTo(static_cast<glm::vec3>(m_gridCell));
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

uint32_t Voxel::color() const {
    return m_color;
}

float Voxel::emissiveness() const {
    return m_emissiveness;
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
        VoxelDebrisGenerator generator;
        generator.setOrientation(worldObject->transform().orientation());
        generator.setPosition(worldObject->transform().applyTo(glm::vec3(m_gridCell)));
        generator.setScale(worldObject->transform().scale() * 0.6f, 0.4f);
        generator.setColor(m_color);
        generator.setForce(0.4f, 0.5f);
        generator.setSpawnProbability(0.5);
        generator.setLifetime(Property<float>("vfx.debrisLifetime"), 0.9f);
        generator.spawn();
    }
}
float Voxel::defaultMass() {
    if (s_defaultMass == nullptr) {
        s_defaultMass = new Property<float>("voxel.DefaultMass");
    }
    return s_defaultMass->get();
}

float Voxel::defaultHp() {
    if (s_defaultHp == nullptr) {
        s_defaultHp = new Property<float>("voxel.DefaultHP");
    }
    return s_defaultHp->get();
}


