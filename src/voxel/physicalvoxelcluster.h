#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "collision/collision.h"
#include "property/property.h"
#include "collidablevoxelcluster.h"

class CollisionDetector;

class PhysicalVoxelCluster : public CollidableVoxelCluster {
public:
    PhysicalVoxelCluster(float scale = 1.0);
    virtual ~PhysicalVoxelCluster();

    std::list<Collision> &move(float delta_sec);
    
    void accelerate(glm::vec3 direction);
    void accelerateAngular(glm::vec3 axis);

    virtual void addVoxel(Voxel *voxel);
    virtual void removeVoxel(const cvec3 &position);

    virtual void finishInitialization();
    virtual void updateSpeed(float delta_sec);

    void speed(glm::vec3 speed);

protected:
    void calculateMassAndCenter();

    void resolveCollision(Collision & c, float delta_sec);
    void applyTransform();
    void doSteppedTransform();
    float calculateStepCount(const WorldTransform & oldTransform, const WorldTransform & newTransform);
    bool isCollisionPossible();

private:
    float m_mass;
    bool m_massValid;

    WorldTransform m_oldTransform;
    WorldTransform m_newTransform;

    glm::vec3 m_speed;
    glm::vec3 m_angularSpeed;
    
    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;

    Property<float> m_dampening;
    Property<float> m_angularDampening;
    Property<float> m_rotationFactor;
};