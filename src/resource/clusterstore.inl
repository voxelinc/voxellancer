#pragma once
#include "voxel/voxelcluster.h"

// The ClusterStore only stores VoxelClusters, thus
// this method is only valid for classes have a copy-constructor from VoxelCluster
template <class T>
T *ClusterStore::create(const std::string& name){
    std::map<std::string, std::unique_ptr<VoxelCluster>>::iterator item = m_items.find(name);
    VoxelCluster *cluster = nullptr;
    if (item == m_items.end()){
        cluster = new VoxelCluster();
        m_loader.loadClusterFromFile((char*)name.c_str(), cluster);
        m_items[name] = std::unique_ptr<VoxelCluster>(cluster);
    } else {
        cluster = item->second.get();
    }
    return new T(*cluster);
}
