#include "voxelexplosiongenerator.h"

#include <list>

#include "worldobject/worldobject.h"


VoxelExplosionGenerator::VoxelExplosionGenerator() :
    prop_spawnCount("vfx.explosionSpawnCount")
{
}

VoxelExplosionGenerator::~VoxelExplosionGenerator() {
}

void VoxelExplosionGenerator::spawnVoxelExplosion(const glm::vec3& position, int color, float spawnRadius, float force, const glm::vec3& impactVector){
    // spawn explosionSpawnCount voxels with color at position within a radius of spawnRadius with a speed of ~force in all directions modified by ~impactVector 
    std::list<WorldObject*> objects;
    // Maximum voxel edge length is spawnRadius * 2 / sqrt(2) for 1 voxel
    float scale = (spawnRadius / 1.4143f) / prop_spawnCount;
    for (int i = 0; i < prop_spawnCount; i++){
        WorldObject* newObject = new WorldObject(scale);
        Voxel* voxel = new Voxel(glm::ivec3(0, 0, 0), color);
        voxel->addToObject(newObject);

        // TODO: position correctly within radius
        newObject->setPosition(position);
        newObject->setCrucialVoxel(glm::ivec3(0, 0, 0));
        //newObject->setS

        objects.push_back(newObject);
    }
}