#pragma once

#include "worldobject/worldobject.h"
#include "worldobject/ship.h"

#include "clustercache.h"


template<typename T>
T* WorldObjectFactory::build(const std::string& name) {
    m_name = name;

    T* worldObject = new T();
    m_worldObject = worldObject;

    m_worldObject->loadCluster(name);
    
    setupHardpoints();
    setupEngineSlots();

    return worldObject;
}

