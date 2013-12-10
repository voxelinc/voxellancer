#include "damageimpactgenerator.h"

#include "worldobject/worldobject.h"

#include "utils/tostring.h"


void DamageImpactGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
    std::list<Impact> damageImpacts;

    for(WorldObjectCollision& worldObjectCollision : worldObjectCollisions) {
        float massPerImpactA = worldObjectCollision.worldObjectA()->physics().mass() / worldObjectCollision.voxelCollisions().size();
        float massPerImpactB = worldObjectCollision.worldObjectB()->physics().mass() / worldObjectCollision.voxelCollisions().size();

        for(VoxelCollision& voxelCollision :  worldObjectCollision.voxelCollisions()) {
            damageImpacts.push_back(Impact(voxelCollision.a().worldObject(), voxelCollision.a().voxel(), voxelCollision.b().speed(), massPerImpactB));
            damageImpacts.push_back(Impact(voxelCollision.b().worldObject(), voxelCollision.b().voxel(), voxelCollision.a().speed(), massPerImpactA));
        }
    }

    m_impactAccumulator.clear();
    m_impactAccumulator.parse(damageImpacts);
}

std::list<Impact>& DamageImpactGenerator::damageImpacts() {
    return m_impactAccumulator.impacts();
}

