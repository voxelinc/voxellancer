#pragma once

#include <map>
#include <memory>
#include <string>
#include <map>
#include <vector>


class Voxel;
class VoxelCluster;
class WorldObject;
class ColorCoder;
class ClusterLoader;

class ClusterCache {

public:
    ClusterCache();
    virtual ~ClusterCache();
    
    void fillObject(WorldObject* worldObject, const std::string& filename);
    void fillCluster(VoxelCluster* cluster, const std::string& filename);

    static ClusterCache *instance();

protected:
    std::vector<Voxel*> * getOrCreate(const std::string& filename);


    std::map<std::string, std::vector<Voxel*>*> m_items;
    std::unique_ptr<ClusterLoader> m_loader;
    std::unique_ptr<ColorCoder> m_colorCoder;

    static ClusterCache *s_instance;
};