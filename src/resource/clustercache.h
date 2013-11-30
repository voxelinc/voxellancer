#pragma once

#include <map>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "clusterloader.h"
#include "colorcoder.h"

class Voxel;

class ClusterCache {

public:
    ClusterCache();
    virtual ~ClusterCache();
    
    void fillCluster(VoxelCluster *cluster, const std::string& filename, bool colorCoded = false);
    static ClusterCache *instance();

private:
    std::map<std::string, std::vector<Voxel*>*> m_items;
    ClusterLoader m_loader;
    ColorCoder m_colorCoder;

    static ClusterCache *s_instance;
};