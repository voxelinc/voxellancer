#pragma once

#include <string>

#include "equipment/weapons/bullet.h"

#include "geometry/transform.h"
#include "geometry/speed.h"


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

    int bufferSlot() const;
    void setBufferSlot(int bufferSlot);

    InstancedBulletContainer* container();

    InstancedBulletData* data();

    bool dataChanged() const;
    void setDataChanged(bool changed);

    virtual void update(float deltaSec) override;

    virtual Transform& transform() override;
    virtual void setTransform(const Transform& transform) override;

    virtual void setSpeed(const Speed& speed) override;

    virtual void spawn() override;
    virtual void remove() override;

    virtual float length() override;


protected:
    void updateData();


protected:
    std::string m_name;
    Transform m_transform;
    Speed m_speed;

    Handle<InstancedBulletContainer> m_container;
    int m_bufferSlot;

    InstancedBulletData m_data;
    bool m_dataChanged;
};

