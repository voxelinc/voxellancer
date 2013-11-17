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
    m_voxeltree(nullptr, *this, Grid3dAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0))),
    m_geode(nullptr),
    m_voxelrenderdata(this),
    m_transform(center, scale),
    m_old_transform(center, scale)
{
}

VoxelCluster::~VoxelCluster() {

}

AABB VoxelCluster::aabb() {
    return AABB::containing(m_voxeltree.boundingSphere());
}

WorldTransform &VoxelCluster::transform() {
    return m_transform;
}

const WorldTransform &VoxelCluster::transform() const {
    return m_transform;
}

static float MAX_STEP_SIZE = 0.1f;

// tries to apply the current transform as far as no collision happens.
// should not be used if the voxelcluster is not part of a worldtree.
void VoxelCluster::applyTransform(bool checkCollision) {
    if (checkCollision) {
        assert(m_worldTree != nullptr);

        bool sth_changed = m_transform.position() != m_old_transform.position();
        sth_changed |= m_transform.orientation() != m_old_transform.orientation();
        if (sth_changed) {
            if (isPossibleCollision())
                doSteppedTransform();
        }
    }
    m_old_transform = m_transform;
    updateGeode();
}

bool VoxelCluster::isPossibleCollision() {
    // the geode aabb is still the old one, add it to the final aabb
    AABB full_aabb = m_geode->aabb().united(aabb());
    // is there someone else than yourself inside?
    return m_worldTree->geodesInAABB(full_aabb).size() > 1; 
}

void VoxelCluster::doSteppedTransform() {
    float distance = glm::length(m_transform.position() - m_old_transform.position());

    float steps = floor(distance / MAX_STEP_SIZE) + 1; // at least one!
    WorldTransform new_transform = m_transform;
    CollisionDetector collisionDetector(*m_worldTree, *this);

    for (int i = 0; i <= steps; i++) {
        m_transform.setOrientation(glm::mix(m_old_transform.orientation(), new_transform.orientation(), i / steps));
        m_transform.setPosition(glm::mix(m_old_transform.position(), new_transform.position(), i / steps));
        updateGeode();
        const std::list<Collision> & collisions = collisionDetector.checkCollisions();
        if (!collisions.empty()) {
            assert(i > 0); // you're stuck, hopefully doesn't happen!
            m_transform.setOrientation(glm::mix(m_old_transform.orientation(), new_transform.orientation(), (i - 1) / steps));
            m_transform.setPosition(glm::mix(m_old_transform.position(), new_transform.position(), (i - 1) / steps));
            break;
        }
    }
}

VoxeltreeNode &VoxelCluster::voxeltree() {
    return m_voxeltree;
}

const VoxeltreeNode &VoxelCluster::voxeltree() const {
    return m_voxeltree;
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

    // Memoryleak as of now, voxeltree shouldn't manage the voxel
    m_voxeltree.insert(new Voxel(voxel));

    m_voxelrenderdata.invalidate();

    updateGeode();
}

void VoxelCluster::removeVoxel(const cvec3 & position) {
    m_voxel.erase(position);
    m_voxeltree.remove(position);
    m_voxelrenderdata.invalidate();
}

const std::unordered_map<cvec3, Voxel, VoxelHash> & VoxelCluster::voxel() const{
    return m_voxel;
}

VoxelRenderData * VoxelCluster::voxelRenderData() {
    return &m_voxelrenderdata;
}

void VoxelCluster::updateGeode() {
    if (m_geode != nullptr) {
        m_geode->setAABB(aabb());
    }
}

void VoxelCluster::setWorldTree(Worldtree* worldTree) {
    m_worldTree = worldTree;
}



