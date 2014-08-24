#pragma once

#include "voxel.h"


template<Axis high, Axis middle, Axis low>
bool VoxelGridCmp<high, middle, low>::operator()(const Voxel* voxel1, const Voxel* voxel2) const {
    if(voxel1->cell()[high] < voxel2->cell()[high]) {
        return true;
    }

    if(voxel1->cell()[high] > voxel2->cell()[high]) {
        return false;
    }

    if(voxel1->cell()[middle] < voxel2->cell()[middle]) {
        return true;
    }

    if(voxel1->cell()[middle] > voxel2->cell()[middle]) {
        return false;
    }

    if(voxel1->cell()[low] < voxel2->cell()[low]) {
        return true;
    }

    return false;
}

