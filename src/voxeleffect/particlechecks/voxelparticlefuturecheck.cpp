#include "voxelparticlefuturecheck.h"

#include <glm/glm.hpp>

#include "geometry/point.h"
#include "geometry/transform.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"
#include "worldobject/worldobject.h"

#include "voxeleffect/voxelparticledata.h"

bool VoxelParticleFutureCheck::intersectsIn(const VoxelParticleData& particle, float futureSecs, const VoxelCluster& against) {
    glm::vec3 position = particle.directionalSpeed * futureSecs + particle.creationPosition;

    glm::ivec3 cell = glm::ivec3(against.transform().inverseApplyTo(position));
    if (against.voxel(cell)) {
        return true;
    }

    return false;
}

