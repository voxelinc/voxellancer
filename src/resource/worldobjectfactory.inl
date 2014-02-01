#pragma once

#include "worldobject/worldobject.h"
#include "worldobject/ship.h"

#include "clustercache.h"


template<typename T>
T* WorldObjectFactory::build(const std::string& name) {
    m_name = name;

    T* worldObject = new T();
    m_worldObject = worldObject;

    std::string clusterFile = Property<std::string>(m_name + ".general.voxelcluster");
    ClusterCache::instance()->fillObject(worldObject, std::string("data/voxelcluster/") + clusterFile);

    setupHardpoints();
    setupEngineSlots();

    return worldObject;
}

