#pragma once

#include <map>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "clusterloader.h"
#include "colorcoder.h"

class Voxel;
class WorldObject;

class ClusterCache {

public:
    ClusterCache();
    virtual ~ClusterCache();
    
    void fillObject(WorldObject *worldObject, const std::string& filename);
    void fillCluster(VoxelCluster *cluster, const std::string& filename);

    static ClusterCache *instance();

protected:
    std::vector<Voxel*> * getOrCreate(const std::string& filename);


    std::map<std::string, std::vector<Voxel*>*> m_items;
    ClusterLoader m_loader;
    ColorCoder m_colorCoder;

    static ClusterCache *s_instance;
};