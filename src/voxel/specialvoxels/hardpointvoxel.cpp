#include "hardpointvoxel.h"

#include "voxel/voxelcluster.h"

HardpointVoxel::HardpointVoxel(){
}

HardpointVoxel::HardpointVoxel(cvec3 gridCell, cvec3 color) :
    Voxel(gridCell, color)
{
}

HardpointVoxel::~HardpointVoxel() {

}

void HardpointVoxel::addToCluster(VoxelCluster *cluster){
    cluster->addVoxel(this);
}
