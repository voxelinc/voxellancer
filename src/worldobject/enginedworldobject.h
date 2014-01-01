#pragma once

#include <vector>
#include "worldobject.h"
#include "world/world.h"
#include "world/god.h"
#include "property/propertymanager.h"
#include "property/property.h"

class Engine;

class EnginedWorldObject : public WorldObject {
public:
    EnginedWorldObject(CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other);
    virtual void update(float deltasec);

    virtual void addEngineVoxel(EngineVoxel* voxel);
    void removeEngine(Engine* engine);

protected:
        
    std::vector<Engine*> m_engines;
};
