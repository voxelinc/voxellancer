#pragma once

#include <list>
#include <memory>

#include "voxel/voxelcluster.h"
#include "handle/handle.h"


class CollisionDetector;
class EngineVoxel;
class HardpointVoxel;
class CockpitVoxel;
class FuelVoxel;
class CollisionFilter;
class Physics;
class ObjectInfo;
class VoxelCollision;

class WorldObject : public VoxelCluster
{
public:
    WorldObject();
    virtual ~WorldObject();

    CollisionFilter& collisionFilter();
    CollisionDetector& collisionDetector();
    Physics& physics();
    ObjectInfo& objectInfo();

    virtual void update(float deltaSec);

    std::list<VoxelCollision>& performMovement(float deltaSec);

    virtual void addVoxel(Voxel* voxel) override;
    virtual void removeVoxel(Voxel* voxel) override;

    virtual void addEngineVoxel(EngineVoxel* voxel);
    virtual void addHardpointVoxel(HardpointVoxel* voxel);
    virtual void addCockpitVoxel(CockpitVoxel* voxel);
    virtual void addFuelVoxel(FuelVoxel* voxel);

    Voxel *crucialVoxel();
    void setCrucialVoxel(const glm::ivec3& cell);

    virtual void accelerate(const glm::vec3& direction);
    virtual void accelerateAngular(const glm::vec3& axis);

    void setCenterAndAdjustPosition(const glm::vec3& newCenter);

    void updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation);

    virtual void onCollision();
    virtual void onSpawnFail();

    Handle<WorldObject>& handle();

    bool scheduledForDeletion();
    void onScheduleForDeletion();


    float collisionFieldOfDamage();

protected:
    bool m_scheduledForDeletion;

    WorldObject(CollisionFilter* collisionFilter, float scale=1.0f);

    std::unique_ptr<CollisionFilter> m_collisionFilter;
    std::unique_ptr<CollisionDetector> m_collisionDetector;
    std::unique_ptr<Physics> m_physics;
    std::unique_ptr<ObjectInfo> m_objectInfo;

    Handle<WorldObject> m_handle;

    Voxel* m_crucialVoxel;

    float m_collisionFieldOfDamage;
};
