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

    VoxelCluster *create(const std::string& name);

    template <class T>
    T *create(const std::string& name);

    static ClusterStore *instance();

private:
    std::map<std::string, std::unique_ptr<VoxelCluster>> m_items;
    ClusterLoader m_loader;

    static ClusterStore *s_instance;

};

#include "clusterstore.inl"
