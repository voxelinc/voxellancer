#pragma once

#include <list>
#include <memory>

#include "collision/collisiondetector.h"
#include "collision/collisionfilterable.h"

#include "worldobject/handle/handle.h"

#include "physics/physics.h"

#include "ui/objectinfo.h"

#include "voxel/voxelcluster.h"


class CollisionDetector;
class EngineVoxel;
class HardpointVoxel;
class CockpitVoxel;
class FuelVoxel;

class WorldObject : public VoxelCluster, public CollisionFilterable {
public:
    WorldObject(CollisionFilterClass collisionFilterClass = CollisionFilterClass::Other, float scale = 1.0f);
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

    Voxel* crucialVoxel();
    void setCrucialVoxel(const glm::ivec3& cell);

    virtual void accelerateDirectional(const glm::vec3& direction);
    virtual void accelerateAngular(const glm::vec3& axis);

    void setCenterAndAdjustPosition(const glm::vec3& newCenter);

    void updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation);

    virtual void onCollision();
    virtual void onSpawnFail();

    Handle<WorldObject>& handle();

    bool scheduledForDeletion();
    void onScheduleForDeletion();


protected:
    CollisionDetector m_collisionDetector;
    Physics m_physics;
    ObjectInfo m_objectInfo;

    Handle<WorldObject> m_handle;

    Voxel* m_crucialVoxel;

    bool m_scheduledForDeletion;
};

