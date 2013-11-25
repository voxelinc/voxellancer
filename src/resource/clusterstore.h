#pragma once

#include <map>
#include <memory>
#include <string>

#include "clusterloader.h"

template<class T>
class ClusterStore {

public:
    ClusterStore();
    virtual ~ClusterStore();
    
    T *create(const std::string& name);
    static ClusterStore *instance();

private:
    std::map<std::string, std::unique_ptr<T>> m_items;
    ClusterLoader m_loader;

    static ClusterStore<T> *s_instance;
};

#include "clusterstore.inl"
