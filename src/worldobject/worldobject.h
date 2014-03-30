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

enum class SpawnState {
    None,
    SpawnScheduled,
    Spawned,
    Rejected,
    RemovalScheduled,
};

enum class WorldObjectType {
    Ship        = 1 << 0,
    Bullet      = 1 << 1,
    Rocket      = 1 << 2,
    Other       = 1 << 3
};

/**
 *  A WorldObject is an Object in our World. Being the second level in the object hierarchy,
 *  it adds CollisionDetection, Physics and SpecialVoxels aka WorldObjectComponents
*/

class WorldObject : public VoxelCluster, public Scriptable {
public:
    WorldObject();
    WorldObject(const Transform& transform);
    virtual ~WorldObject();

    virtual WorldObjectType objectType() const;

    SpawnState spawnState() const;
    void setSpawnState(SpawnState spawnState);

    CollisionFilter& collisionFilter();
    void setCollisionFilter(CollisionFilter* collisionFilter);

    CollisionDetector& collisionDetector();

    Physics& physics();
    const Physics& physics() const;

    ObjectInfo& objectInfo();

    WorldObjectComponents& components();
    const WorldObjectComponents& components() const;

    virtual void update(float deltaSec);

    virtual void addVoxel(Voxel* voxel) override;
    virtual void removeVoxel(Voxel* voxel) override;

    Voxel* crucialVoxel();
    void setCrucialVoxel(const glm::ivec3& cell);
    bool isCrucialVoxelDestroyed();

    void updateTransformAndGeode(const glm::vec3& position, const glm::quat& orientation);

    virtual void onCollision();
    virtual void onSpawnFail();
    //virtual void onWrecked();

    Handle<WorldObject>& handle();

    float collisionFieldOfDamage() const;
    void setCollisionFieldOfDamage(float collisionFieldOfDamage);

    virtual bool passiveForCollisionDetection();


protected:
    std::unique_ptr<CollisionFilter> m_collisionFilter;
    std::unique_ptr<CollisionDetector> m_collisionDetector;
    std::unique_ptr<Physics> m_physics;
    std::unique_ptr<ObjectInfo> m_objectInfo;
    std::unique_ptr<WorldObjectComponents> m_components;

    Handle<WorldObject> m_handle;
    Voxel* m_crucialVoxel;
    bool m_crucialVoxelDestroyed;
    float m_collisionFieldOfDamage;
    SpawnState m_spawnState;
};

