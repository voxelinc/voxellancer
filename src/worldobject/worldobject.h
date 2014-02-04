#pragma once

#include <list>
#include <memory>

#include "collision/collisiondetector.h"
#include "collision/collisionfilterable.h"
#include "physics/physics.h"
#include "voxel/voxelcluster.h"
#include "ui/objectinfo.h"
#include "world/god.h"


class EngineVoxel;
class HardpointVoxel;
class CockpitVoxel;
class FuelVoxel;
class WorldObjectHandle;

class WorldObject : public VoxelCluster, public CollisionFilterable
{
public:
    WorldObject(CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other);
    WorldObject(float scale, CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other);

    virtual ~WorldObject();

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

    std::shared_ptr<WorldObjectHandle> handle() const;

    bool scheduledForDeletion();

    float collisionDamageFOV();

protected:
    // Only god can set this mark. Unfortunately the method will be able to access all our protected members
    friend void God::scheduleRemoval(WorldObject* worldObject);
    void markScheduledForDeletion();
    bool m_scheduledForDeletion;

    CollisionDetector m_collisionDetector;
    Physics m_physics;

    std::shared_ptr<WorldObjectHandle> m_handle;

    ObjectInfo m_objectInfo;
    Voxel* m_crucialVoxel;

    float m_collisionDamageFOV;
};
