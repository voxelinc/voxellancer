#pragma once

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "../collision/collision.h"
#include "../property/property.h"

class PhysicalObject : public VoxelCluster {
public:
    PhysicalObject(float scale = 1.0);
    virtual ~PhysicalObject();

    virtual void update(float delta_sec) override;
    void applyTransform(bool checkCollision = true);
    
    void accelerate(glm::vec3 direction);
    void accelerate_angular(glm::vec3 axis);

    void calculateMassAndCenter();
    
private:
    void doSteppedTransform();
    float calculateStepCount(const WorldTransform & oldTransform, const WorldTransform & newTransform);
    bool isCollisionPossible();
    void handleCollision(const Collision & c);

    float m_mass;
    float m_delta_sec;

    WorldTransform m_oldTransform;
    WorldTransform m_newTransform;

    glm::vec3 m_speed;
    glm::vec3 m_angularSpeed;
    
    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;
    Property<float> m_dampening;
    Property<float> m_angularDampening;
};