#pragma once

#include <list>
#include <memory>

#include "collision/collisiondetector.h"
#include "collision/collisionfilterable.h"
#include "physics/physics.h"
#include "voxel/voxelcluster.h"
#include "ui/objectinfo.h"

class EngineVoxel;
class HardpointVoxel;
class CockpitVoxel;
class FuelVoxel;
class WorldObjectHandle;

class WorldObject : public VoxelCluster, public CollisionFilterable
{
public:
    WorldObject(CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other);
    WorldObject(float scale, glm::vec3 center = glm::vec3(0), CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other);
    WorldObject(const WorldTransform& transform, CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other);

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

protected:
    WorldObject(Physics* physics, CollisionDetector* detector, float scale = 1.0f, CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other);
    std::unique_ptr<CollisionDetector> m_collisionDetector;
    std::unique_ptr<Physics> m_physics;
    std::shared_ptr<WorldObjectHandle> m_handle;
    Voxel* m_crucialVoxel;
    ObjectInfo m_objectInfo;
};
