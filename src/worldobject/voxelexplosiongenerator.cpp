#include "voxelexplosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "worldobject/voxelexplosioncluster.h"
#include "utils/randfloat.h"


VoxelExplosionGenerator::VoxelExplosionGenerator() :
    prop_spawnCount("vfx.explosionSpawnCount"),
    prop_lifetime("vfx.explosionLifetime")
{
}

VoxelExplosionGenerator::~VoxelExplosionGenerator() {
}

void VoxelExplosionGenerator::spawnVoxelExplosion(const glm::vec3& position, int color, float spawnRadius, float force, const glm::vec3& impactVector){
    // spawn explosionSpawnCount voxels with color at position within a radius of spawnRadius with a speed of ~force in all directions modified by ~impactVector 
    // Maximum voxel edge length is spawnRadius * 2 / sqrt(2) for 1 voxel
    float scale = (2 * spawnRadius / 1.4143f) / prop_spawnCount;
    int lowestIndex = (int)-glm::floor(prop_spawnCount / 2.0f);
    int highestIndex = (int)glm::ceil(prop_spawnCount / 2.0f);
    for (int i = lowestIndex; i < highestIndex; i++){
        for (int j = lowestIndex; j < highestIndex; j++){
            for (int k = lowestIndex; k < highestIndex; k++){
                VoxelExplosionCluster* newObject = new VoxelExplosionCluster(0.95f * scale, prop_lifetime * force); //multiply 0.95 to certainly be below the collision threshold
                Voxel* voxel = new Voxel(glm::ivec3(0, 0, 0), color, 0.000001f, 0.1f);
                voxel->addToObject(newObject);
                newObject->setCrucialVoxel(glm::ivec3(0, 0, 0));
                
                // Position voxels in a cube within the save spawn radius
                newObject->setPosition( position +
                    scale * (0.5f + glm::vec3(i, j, k))
                    ); 


                // the further out, the faster the speed
                newObject->physics().setSpeed( force * glm::vec3(    
                    RandFloat::rand(0, 10.0f * (i + 0.5f)), 
                    RandFloat::rand(0, 10.0f * (j + 0.5f)),
                    RandFloat::rand(0, 10.0f * (k + 0.5f)))
                    + impactVector);
                
                newObject->physics().setAngularSpeed(glm::vec3(RandFloat::rand(-10, 10), RandFloat::rand(-10, 10), RandFloat::rand(-10, 10)));

                newObject->finishInitialization();

                World::instance()->god().scheduleSpawn(newObject);
            }
        }
    }
}