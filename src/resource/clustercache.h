#pragma once

#include <map>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "clusterloader.h"

class Voxel;

class ClusterCache {

public:
    ClusterCache();
    virtual ~ClusterCache();
    
    void fillCluster(VoxelCluster *cluster, const std::string& filename);
    static ClusterCache *instance();

private:
    std::map<std::string, std::vector<Voxel*>*> m_items;
    ClusterLoader m_loader;

    static ClusterCache *s_instance;
};

