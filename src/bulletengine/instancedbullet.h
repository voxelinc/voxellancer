#pragma once

#include <memory>
#include <unordered_set>
#include <string>
#include <vector>

#include "collision/collisionfilter.h"

#include "equipment/weapons/bullet.h"

#include "geometry/transform.h"
#include "geometry/speed.h"
#include "geometry/point.h"

#include "worldtree/worldtreehint.h"


class InstancedBulletContainer;

struct InstancedBulletData {
    float active;
    glm::vec3 originPosition;
    glm::vec3 originEulers;
    glm::vec3 directionalSpeed;
    glm::vec3 angularSpeed;
    glm::vec3 center;
    float originTime;
    float deathTime;
};

class InstancedBullet : public Bullet {
public:
    InstancedBullet(const Handle<InstancedBulletContainer>& container, const std::string& name);

    const std::string& name() const;

    bool alive() const;

    void setCreator(WorldObject* creator) override;

    int bufferSlot() const;
    void setBufferSlot(int bufferSlot);

    InstancedBulletContainer* container();

    InstancedBulletData* data();

    const glm::vec3& collisionPoint();

    bool dataChanged() const;
    void setDataChanged(bool changed);

    virtual void update(float deltaSec) override;

    virtual Transform& transform() override;
    virtual void setTransform(const Transform& transform) override;

    virtual void setSpeed(const Speed& speed) override;

    float emissiveness() const;
    virtual const SoundProperties& hitSound() const override;

    virtual void spawn() override;
    virtual void remove() override;

    virtual float length() override;


protected:
    void updateData();
    void updateCollisionPoint();
    Voxel* nearestVoxel(const std::unordered_set<Voxel*> voxels, const glm::vec3& point) const;
    void applyDamage(Voxel* voxel);


protected:
    std::string m_name;
    Transform m_transform;
    Speed m_speed;

    bool m_alive;

    Handle<InstancedBulletContainer> m_container;
    int m_bufferSlot;

    InstancedBulletData m_data;
    bool m_dataChanged;

    glm::vec3 m_collisionPoint;
    std::unique_ptr<CollisionFilter> m_collisionFilter;
    WorldTreeHint m_worldTreeHint;
};

