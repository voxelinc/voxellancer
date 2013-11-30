#include "enginevoxel.h"

#include "voxel/voxelcluster.h"

EngineVoxel::EngineVoxel(){
}

EngineVoxel::EngineVoxel(cvec3 gridCell, cvec3 color) :
    Voxel(gridCell, color)
{
}

EngineVoxel::~EngineVoxel() {

}

void EngineVoxel::addToCluster(VoxelCluster *cluster){
    cluster->addVoxel(this);
}
