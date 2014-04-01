#include "voxel.h"

#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "worldobject/worldobject.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"
#include "voxeleffect/voxeldebrisgenerator.h"


Property<float>* Voxel::s_defaultMass;
Property<float>* Voxel::s_defaultHp;

Voxel::Voxel(const glm::ivec3& gridCell, uint32_t color, float normalizedMass, float hp, float emissiveness):
    m_gridCell(gridCell),
    //m_voxelTreeNode(nullptr),
    m_visuals(color, 0.0f),
    m_normalizedMass(normalizedMass),
    m_hp(hp)
{
    assert(m_normalizedMass > 0.0f);
    assert( gridCell.x >= 0 && gridCell.x < 256 &&
            gridCell.y >= 0 && gridCell.y < 256 &&
            gridCell.z >= 0 && gridCell.z < 256);
}

Voxel::Voxel(const Voxel& other):
    Voxel(other.gridCell(), other.visuals().color(), other.normalizedMass(), other.hp())
{
    m_visuals = other.visuals();
}

Voxel::~Voxel() {
}

const glm::ivec3& Voxel::gridCell() const {
    return m_gridCell;
}

glm::vec3 Voxel::position(const Transform& transform) const {
    return transform.applyTo(glm::vec3(m_gridCell));
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

Visuals Voxel::visuals() const {
    return m_visuals;
}

float Voxel::hp() const {
    return m_hp;
}

void Voxel::applyDamage(float deltaHp) {
    m_hp = std::max(m_hp - deltaHp, 0.0f);
}

float Voxel::damageForwardingDestructionDamage() {
    return 0;
}

float Voxel::normalizedMass() const {
    return m_normalizedMass;
}

void Voxel::onRemoval() {

}

void Voxel::onDestruction(const WorldObject* owner) {
    if (owner) {
        VoxelDebrisGenerator generator(owner);
        generator.setOrientation(owner->transform().orientation());
        generator.setPosition(owner->transform().applyTo(glm::vec3(m_gridCell)));
        generator.setScale(owner->transform().scale() * 0.6f, 0.4f);
        generator.setColor(visuals().color());
        generator.setEmissiveness(visuals().emissiveness());
        generator.setForce(0.4f, 0.5f);
        generator.setSpawnProbability(0.5);
        generator.setLifetime(Property<float>::get("vfx.debrisLifetime"), 0.9f);
        generator.spawn();
    }
}

float Voxel::defaultMass() {
    if (s_defaultMass == nullptr) {
        s_defaultMass = new Property<float>("voxels.default.mass");
    }
    return s_defaultMass->get();
}

float Voxel::defaultHp() {
    if (s_defaultHp == nullptr) {
        s_defaultHp = new Property<float>("voxels.default.hp");
    }
    return s_defaultHp->get();
}


