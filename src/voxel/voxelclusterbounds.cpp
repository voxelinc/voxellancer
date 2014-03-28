#include "voxelclusterbounds.h"

#include "voxelcluster.h"


VoxelClusterBounds::VoxelClusterBounds(VoxelCluster* voxelCluster):
    m_voxelCluster(voxelCluster),
    m_minimalGridSphereValid(false),
    m_minimalGridAABBValid(false),
    m_aabbValid(false)
{
}

void VoxelClusterBounds::addVoxel(Voxel* voxel) {
    m_voxelsXSorted.insert(voxel);
    m_voxelsYSorted.insert(voxel);
    m_voxelsZSorted.insert(voxel);

    m_minimalGridSphereValid = false;
    m_minimalGridAABBValid = false;
    m_aabbValid = false;
}

void VoxelClusterBounds::removeVoxel(Voxel* voxel) {
    m_voxelsXSorted.erase(voxel);
    m_voxelsYSorted.erase(voxel);
    m_voxelsZSorted.erase(voxel);

    m_minimalGridSphereValid = false;
    m_minimalGridAABBValid = false;
    m_aabbValid = false;
}

const GridAABB& VoxelClusterBounds::minimalGridAABB() {
    if(!m_minimalGridAABBValid) {
        calculateMinimalGridAABB();
    }
    return m_minimalGridAABB;
}

const Sphere& VoxelClusterBounds::minimalGridSphere() {
    if(!m_minimalGridSphereValid) {
        calculateMinimalGridSphere();
    }
    return m_minimalGridSphere;
}

const IAABB& VoxelClusterBounds::aabb() {
    if(!m_aabbValid || m_voxelCluster->transform() != m_cachedAABBTransform) {
        m_aabb = calculateAABB(m_voxelCluster->transform());
        m_cachedAABBTransform = m_voxelCluster->transform();
        m_aabbValid = true;
    }
    return m_aabb;
}

IAABB VoxelClusterBounds::aabb(const Transform& transform) {
    return calculateAABB(transform);
}

const Sphere& VoxelClusterBounds::sphere() {
    m_sphere = sphere(m_voxelCluster->transform());
    return m_sphere;
}

Sphere VoxelClusterBounds::sphere(const Transform& transform) {
    Sphere result(minimalGridSphere());

    result.setPosition(transform.applyTo(result.position()));
    result.setRadius(transform.scale() * result.radius());

    return result;
}

void VoxelClusterBounds::calculateMinimalGridAABB() {
    if(m_voxelCluster->voxelCount() > 0) {
        m_minimalGridAABB = GridAABB(
            glm::ivec3((*m_voxelsXSorted.begin())->gridCell().x, (*m_voxelsYSorted.begin())->gridCell().y, (*m_voxelsZSorted.begin())->gridCell().z),
            glm::ivec3((*m_voxelsXSorted.rbegin())->gridCell().x, (*m_voxelsYSorted.rbegin())->gridCell().y, (*m_voxelsZSorted.rbegin())->gridCell().z)
        );
    }
    else {
        m_minimalGridAABB = GridAABB(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0));
    }
    m_minimalGridAABBValid = true;
}

void VoxelClusterBounds::calculateMinimalGridSphere() {
    m_minimalGridSphere.setPosition(glm::vec3(minimalGridAABB().urb() + minimalGridAABB().llf()) / 2.0f);
    // m_gridAABB only contains the center of each voxel so add sqrt(2) to add the distance from center to edge
    m_minimalGridSphere.setRadius((glm::length(glm::vec3(minimalGridAABB().urb() - minimalGridAABB().llf())) + glm::root_two<float>()) / 2.f);
    m_minimalGridSphereValid = true;
}

const IAABB VoxelClusterBounds::calculateAABB(const Transform& transform) {
    glm::vec3 middle = transform.applyTo(minimalGridSphere().position());
    float radius = minimalGridSphere().radius() * transform.scale();

    glm::ivec3 llf(static_cast<glm::ivec3>(middle - glm::vec3(radius, radius, radius)));
    glm::ivec3 urb(static_cast<glm::ivec3>(middle + glm::vec3(radius + 1, radius + 1, radius + 1)));

    return IAABB(llf, urb);
}



