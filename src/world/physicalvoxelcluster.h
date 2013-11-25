#pragma once

#include <glm/glm.hpp>

#include "collision/collision.h"
#include "property/property.h"
#include "worldtree/worldtreecluster.h"

class PhysicalVoxelCluster : public WorldTreeCluster {
public:
    PhysicalVoxelCluster(float scale = 1.0);
    PhysicalVoxelCluster(const PhysicalVoxelCluster & other);
    virtual ~PhysicalVoxelCluster();

    virtual void update(float delta_sec) override;
    
    void accelerate(glm::vec3 direction);
    void accelerate_angular(glm::vec3 axis);

    void finishInitialization();
    void applyTransform(bool checkCollision = true);

protected:
    void calculateMassAndCenter();

    void doSteppedTransform();
    float calculateStepCount(const WorldTransform & oldTransform, const WorldTransform & newTransform);
    bool isCollisionPossible();
    void handleCollision(const Collision & c);

private:
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
    Property<float> m_rotationFactor;
};