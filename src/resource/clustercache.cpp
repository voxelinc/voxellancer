#include "clustercache.h"

#include "voxel/voxel.h"
#include "voxel/voxelcluster.h"
#include "worldobject/worldobject.h"


ClusterCache *ClusterCache::s_instance = nullptr;


ClusterCache::ClusterCache() :
    m_items(),
    m_loader(),
    m_colorCoder()
{
}

ClusterCache::~ClusterCache() {
}

ClusterCache *ClusterCache::instance() {
    if (s_instance == nullptr) {
        s_instance = new ClusterCache();
    }
    return s_instance;
}

void ClusterCache::fillCluster(VoxelCluster *cluster, const std::string& filename){
    assert(cluster != nullptr);
    std::vector<Voxel*> *source = getOrCreate(filename);

    for (Voxel *voxel : *source){
        (new Voxel(*voxel))->addToCluster(cluster);
    }
}

void ClusterCache::fillObject(WorldObject *worldObject, const std::string& filename) {
    assert(worldObject != nullptr);
    std::vector<Voxel*> *source = getOrCreate(filename);

    for (Voxel *voxel : *source) {
        Voxel* clonedVoxel = m_colorCoder.newCodedVoxel(*voxel);
        clonedVoxel->addToObject(worldObject);
    }
}


std::vector<Voxel*> * ClusterCache::getOrCreate(const std::string& filename) {
    std::map<std::string, std::vector<Voxel*>*>::iterator item = m_items.find(filename);

    if (item == m_items.end()) { //load if not loaded yet
        auto source = new std::vector<Voxel*>();
        m_loader.load(filename, source);
        m_items[filename] = source;
        return source;
    }
    return item->second;
}
