#include "voxel.h"

#include <algorithm>
#include <cassert>

#include "glow/logging.hpp"

#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "voxeleffect/voxeldebrisgenerator.h"
#include "voxeleffect/voxelexplosion.h"
#include "voxeleffect/voxelshatterexplosion.h"

#include "worldobject/worldobject.h"


Property<float>* Voxel::s_defaultDensity;
Property<float>* Voxel::s_defaultHp;

Voxel::Voxel(const glm::ivec3& gridCell, uint32_t color, float density, float hp, float emissiveness):
    m_gridCell(gridCell),
    m_voxelTreeNode(nullptr),
    m_visuals(color, 0.0f),
    m_density(density),
    m_hp(hp)
{
    assert(m_density > 0.0f);
    assert( gridCell.x >= 0 && gridCell.x < 256 &&
            gridCell.y >= 0 && gridCell.y < 256 &&
            gridCell.z >= 0 && gridCell.z < 256);
}

Voxel::Voxel(const Voxel& other):
    Voxel(other.gridCell(), other.visuals().color(), other.density(), other.hp())
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

float Voxel::density() const {
    return m_density;
}

void Voxel::onRemoval() {

}

void Voxel::onDestruction(float energy) {
    destructionExplosion(energy)->spawn();
}

std::shared_ptr<VoxelExplosion> Voxel::destructionExplosion(float energy) {
    return std::make_shared<VoxelShatterExplosion>(*this, energy);
}

float Voxel::defaultDensity() {
    if (s_defaultDensity == nullptr) {
        s_defaultDensity = new Property<float>("voxels.default.density");
    }
    return s_defaultDensity->get();
}

float Voxel::defaultHp() {
    if (s_defaultHp == nullptr) {
        s_defaultHp = new Property<float>("voxels.default.hp");
    }
    return s_defaultHp->get();
}


