#pragma once

#include <map>
#include <memory>
#include <string>

#include "clusterloader.h"
class VoxelCluster;

class ClusterStore {

public:
	ClusterStore();
	virtual ~ClusterStore();
	std::unique_ptr<VoxelCluster> getItem(const std::string& name);

	static ClusterStore *getInstance();

private:
	std::map<std::string, std::unique_ptr<VoxelCluster>> m_items;
	ClusterLoader m_loader;

	static ClusterStore *s_instance;
};