#pragma once

#include <list>
#include <memory>

#include "physics/physics.h"

#include "ui/objectinfo.h"

#include "voxel/voxelcluster.h"

#include "worldobject/handle/handle.h"

#include "worldobjectcomponents.h"


class CollisionDetector;
class EngineVoxel;
class HardpointVoxel;
class CockpitVoxel;
class FuelVoxel;
class CollisionFilter;


class WorldObject : public VoxelCluster {
public:
    WorldObject();
    virtual ~WorldObject();

    CollisionFilter& collisionFilter();
    void setCollisionFilter(CollisionFilter* collisionFilter);

    CollisionDetector& collisionDetector();
    Physics& physics();
    ObjectInfo& objectInfo();
    WorldObjectComponents& components();

    virtual void update(float deltaSec);

    virtual void addVoxel(Voxel* voxel) override;
    virtual void removeVoxel(Voxel* voxel) override;

    Voxel* crucialVoxel();
    void setCrucialVoxel(const glm::ivec3& cell);

    void updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation);

    virtual void onCollision();
    virtual void onSpawnFail();

    Handle<WorldObject>& handle();

    bool scheduledForDeletion();
    void onScheduleForDeletion();


protected:
    std::unique_ptr<CollisionFilter> m_collisionFilter;
    std::unique_ptr<CollisionDetector> m_collisionDetector;
    Physics m_physics;
    ObjectInfo m_objectInfo;
    WorldObjectComponents m_components;

    Handle<WorldObject> m_handle;

    Voxel* m_crucialVoxel;

    bool m_scheduledForDeletion;


    WorldObject(CollisionFilter* collisionFilter, float scale = 1.0f);
};

