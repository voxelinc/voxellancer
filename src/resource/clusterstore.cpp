#include "clusterstore.h"

#include "voxel/voxelcluster.h"

ClusterStore *ClusterStore::s_instance = nullptr;


ClusterStore::ClusterStore():
	m_items(),
	m_loader()
{

}

ClusterStore::~ClusterStore(){

}

VoxelCluster *ClusterStore::create(const std::string& name){
	return create<VoxelCluster>(name);
}

ClusterStore *ClusterStore::instance(){
	if (s_instance == nullptr) {
		s_instance = new ClusterStore();
	}
	return s_instance;
}
