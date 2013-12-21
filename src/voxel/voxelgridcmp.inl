#pragma once

template<Axis highPriorityAxis, Axis middlePriorityAxis, Axis lowPriorityAxis>
bool VoxelGridCmp<highPriorityAxis, middlePriorityAxis, lowPriorityAxis>::operator()(const Voxel* voxel1, const Voxel* voxel2) const {
    if(voxel1->gridCell()[highPriorityAxis] < voxel2->gridCell()[highPriorityAxis]) {
        return true;
    }
    else if(voxel1->gridCell()[highPriorityAxis] > voxel2->gridCell()[highPriorityAxis]) {
        return false;
    }

    if(voxel1->gridCell()[middlePriorityAxis] < voxel2->gridCell()[middlePriorityAxis]) {
        return true;
    }
    else if(voxel1->gridCell()[middlePriorityAxis] > voxel2->gridCell()[middlePriorityAxis]) {
        return false;
    }

    if(voxel1->gridCell()[lowPriorityAxis] < voxel2->gridCell()[lowPriorityAxis]) {
        return true;
    }
    else {
        return false;
    }
}

