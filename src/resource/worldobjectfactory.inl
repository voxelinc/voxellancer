#pragma once

template<typename T>
T* WorldObjectFactory::build(const std::string& name) {
    m_name = name;

    T* worldObject = new Ship();
    m_worldObject = worldObject;

    std::string clusterFile = Property<std::string>(name + ".general.voxelcluster");
    ClusterCache::instance()->fillObject(ship, std::string("data/voxelcluster/") + clusterFile);

    setupHardpoints();
    setupEngineSlots();

    return worldObject;
}
