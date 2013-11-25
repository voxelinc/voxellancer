#include "clusterstore.h"

#include "voxel/voxelcluster.h"
#include "world/physicalvoxelcluster.h"
#include "ui/hudelement.h"

// define here which VoxelCluster types can be stored

template<>
ClusterStore<VoxelCluster> *ClusterStore<VoxelCluster>::s_instance = nullptr;

template<>
ClusterStore<PhysicalVoxelCluster> *ClusterStore<PhysicalVoxelCluster>::s_instance = nullptr;

template<>
ClusterStore<HUDElement> *ClusterStore<HUDElement>::s_instance = nullptr;


