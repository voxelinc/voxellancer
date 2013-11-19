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

std::unique_ptr<VoxelCluster> ClusterStore::getItem(const std::string& name){
	std::map<std::string, std::unique_ptr<VoxelCluster>>::iterator item = m_items.find(name);
	VoxelCluster *cluster = nullptr;
	if (item == m_items.end()){
		cluster = new VoxelCluster();
		m_loader.loadClusterFromFile((char*)name.c_str(), cluster);
		m_items[name] = std::unique_ptr<VoxelCluster>(cluster);
	} else {
		cluster = item->second.get();
	}
	return std::unique_ptr<VoxelCluster>(new VoxelCluster(*cluster));
}

ClusterStore *ClusterStore::getInstance(){
	if (s_instance == nullptr) {
		s_instance = new ClusterStore();
	}
	return s_instance;
}