#include "shockwave.h"

#include <cassert>

#include "geometry/ray.h"

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "world/helper/damageimpact.h"
#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreequery.h"


Shockwave::Shockwave(const Sphere& sphere, float damage, const WorldTreeHint& worldTreeHint):
    m_sphere(sphere),
    m_damage(damage),
    m_worldTreeHint(worldTreeHint)
{
    assert(m_sphere.radius() > 0);
}

std::list<DamageImpact> Shockwave::generateDamageImpacts() {
    std::list<DamageImpact> result;
    WorldTreeQuery query(&World::instance()->worldTree(), &m_sphere, m_worldTreeHint.node());
    m_potentialVoxels = query.intersectingVoxels(); // All voxels in sphere
    std::unordered_set<Voxel*> surfaceVoxels; // Voxels on the surface, thus affected

    for (Voxel* voxel : m_potentialVoxels) {
        if (!isVoxelObscured(voxel)) {
            surfaceVoxels.insert(voxel);
        }
    }

    for (Voxel* voxel : surfaceVoxels) {
        float scale = voxel->voxelTreeNode()->voxelTree()->worldObject()->transform().scale();
        float radius = Voxel::collisionRadius(scale);
        m_voxelSpheres.emplace(voxel, std::unique_ptr<Sphere>(new Sphere(voxel->position(), radius)));
    }

    for (Voxel* voxel : surfaceVoxels) {
        result.push_back(getImpactOnVoxel(voxel));
    }

    return result;
}

bool Shockwave::isVoxelObscured(Voxel* voxel) {
    Ray ray(Ray::fromTo(m_sphere.position(), voxel->position()));

    for (Voxel* potentialOccluder : m_potentialVoxels) {
        if (voxel == potentialOccluder) {
            continue;
        }

        auto iter = m_voxelSpheres.find(potentialOccluder);
        assert(iter != m_voxelSpheres.end());

        Sphere* sphere = iter->second.get();
        if (ray.intersects(*sphere)) {
            return true;
        }
    }

    return false;
}

DamageImpact Shockwave::getImpactOnVoxel(Voxel* voxel) {
    glm::vec3 delta = voxel->position() - m_sphere.position();

    float relativeDamage = glm::length(delta) / m_sphere.radius();
    float damage = relativeDamage * m_damage;
    glm::vec3 damageVec = glm::normalize(delta) * damage;

    WorldObject* worldObject = voxel->voxelTreeNode()->voxelTree()->worldObject();

    return DamageImpact(worldObject, voxel, damageVec, glm::pi<float>());
}
