#include "clustercache.h"

#include "voxel/voxel.h"
#include "voxel/voxelcluster.h"
#include "world/worldobject.h"


ClusterCache *ClusterCache::s_instance = nullptr;


ClusterCache::ClusterCache() :
    m_items(),
    m_loader() 
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



void ClusterCache::fillCluster(WorldObject *worldObject, const std::string& filename) {
    std::vector<Voxel*> *source = getOrCreate(filename);

    for (Voxel *voxel : *source) {
        worldObject->addVoxel(voxel->clone()); // addVoxel(colorcodeAndClone(voxel));
    }
    worldObject->finishInitialization();
}


void ClusterCache::fillCluster(Drawable *cluster, const std::string& filename){
    assert(cluster != nullptr);
    std::vector<Voxel*> *source = getOrCreate(filename);
    
    for (Voxel *voxel : *source){
        cluster->voxelCluster().addVoxel(voxel->clone());
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
