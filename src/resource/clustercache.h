#pragma once

#include <map>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "clusterloader.h"

class Voxel;
class WorldObject;

class ClusterCache {

public:
    ClusterCache();
    virtual ~ClusterCache();
    
    void fill(WorldObject *worldObject, const std::string& filename);
    void fill(VoxelCluster *cluster, const std::string& filename);

    std::vector<Voxel*> * getOrCreate(const std::string& filename);

    static ClusterCache *instance();

private:
    std::map<std::string, std::vector<Voxel*>*> m_items;
    ClusterLoader m_loader;

    static ClusterCache *s_instance;
};

