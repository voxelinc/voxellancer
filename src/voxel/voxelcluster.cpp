#include "voxelcluster.h"

#include <iostream>
#include <list>

#include <glm/gtc/quaternion.hpp>

#include <glow/DebugMessageOutput.h>
#include <glow/ChangeListener.h>
#include <glow/logging.h>
#include <glowutils/MathMacros.h>


#include "utils/tostring.h"
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"


VoxelCluster::VoxelCluster(glm::vec3 center, float scale): 
    m_voxel(),
    m_voxelTree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_geode(nullptr),
    m_voxelRenderData(this),
    m_transform(center, scale),
    m_oldTransform(center, scale)
{
}

VoxelCluster::VoxelCluster(const VoxelCluster& other):
	m_voxel(other.m_voxel),
	m_voxelTree(other.m_voxelTree, this),
	m_geode(nullptr),
	m_voxelRenderData(this),
	m_transform(other.m_transform),
	m_oldTransform(other.m_oldTransform)
{
	
}

VoxelCluster::~VoxelCluster() {

}

AABB VoxelCluster::aabb() {
    return AABB::containing(m_voxelTree.boundingSphere());
}

WorldTransform &VoxelCluster::transform() {
    return m_transform;
}

const WorldTransform &VoxelCluster::transform() const {
    return m_transform;
}

static float MAX_TRANSLATION_STEP_SIZE = 0.1f;
static float MAX_ANGLE_STEP_SIZE = 10.0f;

// tries to apply the current transform as far as no collision happens.
// should not be used if the voxelcluster is not part of a worldtree.
void VoxelCluster::applyTransform(bool checkCollision) {
    if (checkCollision) {
        assert(m_geode != nullptr);

        bool sthChanged = m_transform.position() != m_oldTransform.position();
        sthChanged |= m_transform.orientation() != m_oldTransform.orientation();
        if (sthChanged) {
            if (isCollisionPossible())
                doSteppedTransform();
        }
    }
    m_oldTransform = m_transform;
    updateGeode();
}

bool VoxelCluster::isCollisionPossible() {
    // the geode aabb is still the old one, add it to the final aabb
    AABB fullAabb = m_geode->aabb().united(aabb());
    // is there someone else than yourself inside?
    return m_worldTree->geodesInAABB(fullAabb).size() > 1; 
}

void VoxelCluster::doSteppedTransform() {
    float steps = calculateStepCount();

    WorldTransform new_transform = m_transform;
    CollisionDetector collisionDetector(*m_worldTree, *this);

    for (int i = 0; i <= steps; i++) {
        m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), new_transform.orientation(), i / steps));
        m_transform.setPosition(glm::mix(m_oldTransform.position(), new_transform.position(), i / steps));
        updateGeode();
        const std::list<Collision> & collisions = collisionDetector.checkCollisions();
        if (!collisions.empty()) {
            assert(i > 0); // you're stuck, hopefully doesn't happen!
            m_transform.setOrientation(glm::mix(m_oldTransform.orientation(), new_transform.orientation(), (i - 1) / steps));
            m_transform.setPosition(glm::mix(m_oldTransform.position(), new_transform.position(), (i - 1) / steps));
            break;
        }
    }
}

float VoxelCluster::calculateStepCount()
{
    float distance = glm::length(m_transform.position() - m_oldTransform.position());
    float angle = glm::degrees(2 * glm::acos(glm::dot(m_transform.orientation(), m_oldTransform.orientation())));
    float steps = glm::floor(distance / MAX_TRANSLATION_STEP_SIZE) + 1.f; // at least one!
    steps = glm::max(steps, glm::floor(angle / MAX_ANGLE_STEP_SIZE) + 1.f);
    return steps;
}


VoxeltreeNode &VoxelCluster::voxeltree() {
    return m_voxelTree;
}

const VoxeltreeNode &VoxelCluster::voxeltree() const {
    return m_voxelTree;
}

WorldtreeGeode *VoxelCluster::geode() {
    return m_geode;
}

const WorldtreeGeode *VoxelCluster::geode() const {
    return m_geode;
}

void VoxelCluster::setGeode(WorldtreeGeode *geode) {
    m_geode = geode;

    updateGeode();
}

void VoxelCluster::addVoxel(const Voxel & voxel) {
    // TODO aabb extent(vec3)
    m_voxel[voxel.gridCell()] = voxel;

    // TODO Memoryleak as of now, voxeltree shouldn't manage the voxel
    m_voxelTree.insert(new Voxel(voxel));

    m_voxelRenderData.invalidate();

    updateGeode();
}

void VoxelCluster::removeVoxel(const cvec3 & position) {
    m_voxel.erase(position);
    m_voxelTree.remove(position);
    m_voxelRenderData.invalidate();
}

const std::unordered_map<cvec3, Voxel, VoxelHash> & VoxelCluster::voxel() const{
    return m_voxel;
}

VoxelRenderData * VoxelCluster::voxelRenderData() {
    return &m_voxelRenderData;
}

void VoxelCluster::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void VoxelCluster::setWorldTree(Worldtree* worldTree) {
    m_worldTree = worldTree;
}



