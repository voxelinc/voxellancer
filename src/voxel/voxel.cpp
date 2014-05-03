#include "voxel.h"

#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "worldobject/worldobject.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"
#include "voxeleffect/voxeldebrisgenerator.h"


Property<float>* Voxel::s_defaultUnscaledMass;
Property<float>* Voxel::s_defaultHp;

Voxel::Voxel(const glm::ivec3& gridCell, uint32_t color, float unscaledMass, float hp, float emissiveness):
    m_gridCell(gridCell),
    m_voxelTreeNode(nullptr),
    m_visuals(color, 0.0f),
    m_unscaledMass(unscaledMass),
    m_hp(hp)
{
    assert(m_unscaledMass > 0.0f);
    assert( gridCell.x >= 0 && gridCell.x < 256 &&
            gridCell.y >= 0 && gridCell.y < 256 &&
            gridCell.z >= 0 && gridCell.z < 256);
}

Voxel::Voxel(const Voxel& other):
    Voxel(other.gridCell(), other.visuals().color(), other.unscaledMass(), other.hp())
{
    m_visuals = other.visuals();
}

Voxel::~Voxel() {
}

const glm::ivec3& Voxel::gridCell() const {
    return m_gridCell;
}

glm::vec3 Voxel::position() const {
    assert(m_voxelTreeNode);
    return m_voxelTreeNode->voxelTree()->worldObject()->transform().applyTo(glm::vec3(m_gridCell));
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

float Voxel::unscaledMass() const {
    return m_unscaledMass;
}

void Voxel::onRemoval() {

}

void Voxel::onDestruction(float energy) {
    assert(m_voxelTreeNode);

    WorldObject* worldObject = m_voxelTreeNode->voxelTree()->worldObject();

    if (m_voxelTreeNode && worldObject) {
        VoxelDebrisGenerator generator(worldObject);
        generator.setOrientation(worldObject->transform().orientation());
        generator.setPosition(worldObject->transform().applyTo(glm::vec3(m_gridCell)));
        generator.setScale(worldObject->transform().scale() * 0.8, 0.2f);
        generator.setColor(visuals().color());
        generator.setEmissiveness(visuals().emissiveness());
        generator.setForce(0.0015f * energy + 0.4f, 0.5f);
        generator.setSpawnProbability(0.8f);
        generator.setLifetime(Property<float>("vfx.debrisLifetime"), 0.9f);
        generator.spawn();
    }
}

float Voxel::defaultUnscaledMass() {
    if (s_defaultUnscaledMass == nullptr) {
        s_defaultUnscaledMass = new Property<float>("voxels.default.mass");
    }
    return s_defaultUnscaledMass->get();
}

float Voxel::defaultHp() {
    if (s_defaultHp == nullptr) {
        s_defaultHp = new Property<float>("voxels.default.hp");
    }
    return s_defaultHp->get();
}


