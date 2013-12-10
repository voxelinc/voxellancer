#include "elasticimpactgenerator.h"

#include <iostream>
#include <cassert>

#include "worldobject/worldobject.h"

#include "utils/tostring.h"


void ElasticImpactGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
    m_worldObjectImpacts.clear();

    for(WorldObjectCollision& worldObjectCollision : worldObjectCollisions) {
        assert(worldObjectCollision.voxelCollisions().size());

        // One representative, getting all the mass-power of the impact
        VoxelCollision voxelCollision = worldObjectCollision.voxelCollisions().front();

        m_worldObjectImpacts.push_back(Impact(voxelCollision.a().worldObject(), voxelCollision.a().voxel(), voxelCollision.b().speed(), voxelCollision.b().worldObject()->physics().mass()));
        m_worldObjectImpacts.push_back(Impact(voxelCollision.b().worldObject(), voxelCollision.b().voxel(), voxelCollision.a().speed(), voxelCollision.a().worldObject()->physics().mass()));
    }
}

std::list<Impact>& ElasticImpactGenerator::worldObjectImpacts() {
    return m_worldObjectImpacts;
}
