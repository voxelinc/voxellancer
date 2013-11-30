#include "cockpitvoxel.h"

#include "voxel/voxelcluster.h"

CockpitVoxel::CockpitVoxel(){
}

CockpitVoxel::CockpitVoxel(cvec3 gridCell, cvec3 color) :
    Voxel(gridCell, color)
{
}

CockpitVoxel::~CockpitVoxel() {

}

void CockpitVoxel::addToCluster(VoxelCluster *cluster){
    cluster->addVoxel(this);
}
