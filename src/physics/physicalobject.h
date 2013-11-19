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

    void calculateMassAndCenter();
    
private:
    void doSteppedTransform();
    float calculateStepCount();
    bool isCollisionPossible();
    void handleCollision(const Collision & c);

    float m_mass;
    glm::vec3 m_speed;
    glm::quat m_angular_speed;

    glm::vec3 m_acceleration;
    glm::quat m_angular_acceleration;
    Property<float> m_dampening;
};