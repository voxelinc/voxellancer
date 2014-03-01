#pragma once

#include <list>
#include <memory>

#include "scripting/scriptable.h"

#include "utils/handle/handle.h"

#include "voxel/voxelcluster.h"

class CollisionDetector;
class EngineVoxel;
class HardpointVoxel;
class CockpitVoxel;
class FuelVoxel;
class CollisionFilter;
class Physics;
class ObjectInfo;
class VoxelCollision;
class WorldObjectComponents;

enum class WorldObjectType {
    WorldObject = 1 << 0,
    Ship        = 1 << 1,
    Bullet      = 1 << 2,
    Rocket      = 1 << 3,
    Other       = 1 << 4
};

class WorldObject : public VoxelCluster, public Scriptable {
public:
    WorldObject();
    virtual ~WorldObject();

    virtual WorldObjectType objectType() const;
    virtual ScriptableType scriptableType() const override;

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

    bool scheduledForDeletion() const;
    void onScheduleForDeletion();

    float collisionFieldOfDamage() const;
    void setCollisionFieldOfDamage(float collisionFieldOfDamage);


protected:
    std::unique_ptr<CollisionFilter> m_collisionFilter;
    std::unique_ptr<CollisionDetector> m_collisionDetector;
    std::unique_ptr<Physics> m_physics;
    std::unique_ptr<ObjectInfo> m_objectInfo;
    std::unique_ptr<WorldObjectComponents> m_components;

    Handle<WorldObject> m_handle;
    Voxel* m_crucialVoxel;
    bool m_scheduledForDeletion;
    float m_collisionFieldOfDamage;

    WorldObject(CollisionFilter* collisionFilter, float scale = 1.0f);
};

