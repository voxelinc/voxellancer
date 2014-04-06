#include "instancedbulletvoxeldata.h"

#include "voxel/voxel.h"


InstancedBulletVoxelData::InstancedBulletVoxelData(Voxel* voxel) {
    cell = voxel->gridCell();
    color = voxel->visuals().color();
    emissiveness = voxel->visuals().emissiveness();
}

