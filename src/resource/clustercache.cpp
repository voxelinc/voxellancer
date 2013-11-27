#include "clustercache.h"

#include "voxel/voxel.h"
#include "voxel/voxelcluster.h"


ClusterCache *ClusterCache::s_instance = nullptr;


ClusterCache::ClusterCache() :
m_items(),
m_loader() {

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
    std::map<std::string, std::vector<Voxel*>*>::iterator item = m_items.find(filename);
    std::vector<Voxel*> *source;

    if (item == m_items.end()){ //load if not loaded yet
        source = new std::vector<Voxel*>();
        //m_loader.loadClusterToList(filename, &newItem);
        m_items[filename] = source;
    } else {
        source = item->second;
    }


    for (Voxel *voxel : *source){
        //voxel->addToCluster(cluster);
    }
    cluster->finishInitialization();    
}