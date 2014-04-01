#include "voxelparticleintersectioncheck.h"

#include "geometry/point.h"
#include "geometry/sphere.h"
#include "geometry/transform.h"

#include "world/world.h"

#include "worldobject/ship.h"

#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"

#include "voxel/voxelclusterbounds.h"

#include "voxeleffect/voxelparticledata.h"
#include "voxeleffect/voxelparticleengine.h"

#include "player.h"
#include "camera/camerahead.h"

VoxelParticleIntersectionCheck::VoxelParticleIntersectionCheck(const VoxelParticleEngine& engine) :
    m_particleEngine(engine)
{
}

bool VoxelParticleIntersectionCheck::isDead(const VoxelParticleData& particleData) {
    float timeDelta = m_particleEngine.time() - particleData.creationTime;
    glm::vec3 position = particleData.directionalSpeed * timeDelta + particleData.creationPosition;

    if (!m_Sphere.intersects(Sphere(position, particleData.scale))) {
        return false;
    }

    WorldObject* object = World::instance()->player().ship();
    glm::ivec3 cell = glm::ivec3(object->transform().inverseApplyTo(position));
    if (object->voxel(cell)) {
        return true;
    }    

    return false;
}


void VoxelParticleIntersectionCheck::beforeCheck() {
    if (World::instance()->player().ship()) {
        m_Sphere = World::instance()->player().ship()->bounds().sphere();
    } else {
        m_Sphere = Sphere();
    }

}
