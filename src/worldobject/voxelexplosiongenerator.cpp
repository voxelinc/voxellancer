#include "voxelexplosiongenerator.h"

#include <ctime>

#include "world/god.h"
#include "world/world.h"
#include "worldobject/voxelexplosioncluster.h"


VoxelExplosionGenerator::VoxelExplosionGenerator() :
    prop_spawnCount("vfx.explosionSpawnCount")
{
    std::srand((unsigned int)time(NULL));
}

VoxelExplosionGenerator::~VoxelExplosionGenerator() {
}

void VoxelExplosionGenerator::spawnVoxelExplosion(const glm::vec3& position, int color, float spawnRadius, float force, const glm::vec3& impactVector){
    // spawn explosionSpawnCount voxels with color at position within a radius of spawnRadius with a speed of ~force in all directions modified by ~impactVector 
    // Maximum voxel edge length is spawnRadius * 2 / sqrt(2) for 1 voxel
    float scale = (2 * spawnRadius / 1.4143f) / prop_spawnCount;
    for (int i = 0; i < prop_spawnCount; i++){
        for (int j = 0; j < prop_spawnCount; j++){
            for (int k = 0; k < prop_spawnCount; k++){
                VoxelExplosionCluster* newObject = new VoxelExplosionCluster(0.95f * scale, 10.0f); //multiply 0.95 to certainly be below the collision threshold
                Voxel* voxel = new Voxel(glm::ivec3(0, 0, 0), color);
                voxel->addToObject(newObject);
                newObject->setCrucialVoxel(glm::ivec3(0, 0, 0));
                
                // Position voxels in a cube
                newObject->setPosition( position +
                    ((spawnRadius / 1.4143f) * glm::vec3(-1, -1, -1)) +  // lower corner
                    scale * (0.5f + glm::vec3(i, j, k))
                    ); 

                newObject->physics().setSpeed( force * glm::vec3(    
                    (i < prop_spawnCount / 2 ? -1 : 1) * ((std::rand() % 100)) / 10.0f, 
                    (j < prop_spawnCount / 2 ? -1 : 1) * ((std::rand() % 100)) / 10.0f,
                    (k < prop_spawnCount / 2 ? -1 : 1) * ((std::rand() % 100)) / 10.0f)
                    + impactVector);
                
                newObject->physics().setAngularSpeed(glm::vec3(((std::rand() % 100) - 50) / 100.0f, ((std::rand() % 100) - 50) / 100.0f, ((std::rand() % 100) - 50) / 100.0f));

                newObject->finishInitialization();

                World::instance()->god().scheduleSpawn(newObject);
            }
        }
    }
}