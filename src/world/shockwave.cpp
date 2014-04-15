#include "shockwave.h"

#include <cassert>
#include <iostream>

#include "geometry/ray.h"

#include "voxel/voxel.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"

#include "world/helper/damageimpact.h"
#include "world/world.h"
#include "world/worldlogic.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreenode.h"
#include "worldtree/worldtreequery.h"


Shockwave::Shockwave(float radius, float damage):
    m_sphere(glm::vec3(0.0f), radius),
    m_damage(damage)
{
    assert(m_sphere.radius() > 0);
}

void Shockwave::trigger(const glm::vec3& position, const WorldTreeHint& worldTreeHint) {
    m_sphere.setPosition(position);
    m_worldTreeHint = worldTreeHint;

    std::list<DamageImpact> damageImpacts(generateDamageImpacts());

    for (DamageImpact& damageImpact : damageImpacts) {
        World::instance()->worldLogic().addDamageImpact(damageImpact);
    }
}

std::list<DamageImpact> Shockwave::generateDamageImpacts() {
    std::list<DamageImpact> result;

    WorldTreeQuery query(&World::instance()->worldTree(), &m_sphere, m_worldTreeHint.node());
    m_potentialVoxels = query.intersectingVoxels(); // All voxels in the sphere
    if (query.containingNode()) {
        m_worldTreeHint = query.containingNode()->hint();
    }

    std::unordered_set<Voxel*> surfaceVoxels; // Voxels on the surface, thus affected
    std::cout << "Potential voxels: " << m_potentialVoxels.size() << std::endl;
    for (Voxel* voxel : m_potentialVoxels) {
        if (!isVoxelObscured(voxel)) {
            surfaceVoxels.insert(voxel);
        }
    }

    for (Voxel* voxel : surfaceVoxels) {
        result.push_back(getImpactOnVoxel(voxel));
    }

    return result;
}

bool Shockwave::isVoxelObscured(Voxel* voxel) {
    Line line(m_sphere.position(), voxel->position());

    WorldTreeQuery query(&World::instance()->worldTree(), &line, m_worldTreeHint.node());

    return query.intersectingVoxels().size() > 1;
}

DamageImpact Shockwave::getImpactOnVoxel(Voxel* voxel) {
    glm::vec3 delta = voxel->position() - m_sphere.position();

    float relativeDamage = glm::length(delta) / m_sphere.radius();
    float damage = relativeDamage * m_damage;
    glm::vec3 damageVec = glm::normalize(delta) * damage;

    WorldObject* worldObject = voxel->voxelTreeNode()->voxelTree()->worldObject();

    return DamageImpact(worldObject, voxel, damageVec, glm::pi<float>());
}

