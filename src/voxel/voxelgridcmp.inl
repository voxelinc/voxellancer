#pragma once

#include "voxel.h"

template<Axis high, Axis middle, Axis low>
bool VoxelGridCmp<high, middle, low>::operator()(const Voxel* voxel1, const Voxel* voxel2) const {
    if(voxel1->gridCell()[high] < voxel2->gridCell()[high]) {
        return true;
    }
    
    if(voxel1->gridCell()[high] > voxel2->gridCell()[high]) {
        return false;
    }

    if(voxel1->gridCell()[middle] < voxel2->gridCell()[middle]) {
        return true;
    }
    
    if(voxel1->gridCell()[middle] > voxel2->gridCell()[middle]) {
        return false;
    }

    if(voxel1->gridCell()[low] < voxel2->gridCell()[low]) {
        return true;
    }
       
    return false;
}

