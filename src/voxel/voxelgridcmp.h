#pragma once

class Voxel;

template<Axis highPriorityAxis, Axis middlePriorityAxis, Axis lowPriorityAxis>
class VoxelGridCmp {
public:
    bool operator()(const Voxel* voxel1, const Voxel* voxel2) const;
};


#include "voxelgridcmp.inl"
