#pragma once

#include <list>
#include <memory>

#include "collision/collisiondetector.h"
#include "physics/physics.h"
#include "voxel/voxelcluster.h"
#include "ui/objectinfo.h"

class EngineVoxel;
class HardpointVoxel;
class CockpitVoxel;
class FuelVoxel;

class WorldObject : public VoxelCluster
{
public:
    WorldObject(float scale = 1.0f, glm::vec3 center = glm::vec3(0));
    WorldObject(const WorldTransform& transform);
    virtual ~WorldObject();

    CollisionDetector& collisionDetector();
    Physics& physics();
    ObjectInfo& objectInfo();

    AABB aabb();
    Sphere sphere();

    virtual void update(float delta_sec);

    std::list<Impact>& updatePosition(float delta_sec);

    void addVoxel(Voxel* voxel);
    virtual void addEngineVoxel(EngineVoxel* voxel);
    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    virtual void addCockpitVoxel(CockpitVoxel* voxel);
    virtual void addFuelVoxel(FuelVoxel* voxel);
    void removeVoxel(const glm::ivec3& position);
    
    void finishInitialization();
    void recalculateCenterAndMass();

    Voxel *crucialVoxel();
    void setCrucialVoxel(glm::ivec3 pos);

    virtual void accelerate(glm::vec3 direction);
    virtual void accelerateAngular(glm::vec3 axis);

    virtual void onImpact();
    virtual void onSpawnFail();

protected:
    WorldObject(Physics* physics, CollisionDetector* detector, float scale = 1.0f);
    std::unique_ptr<CollisionDetector> m_collisionDetector;
    std::unique_ptr<Physics> m_physics;
    Voxel * m_crucialVoxel;
    ObjectInfo m_objectInfo;
};
