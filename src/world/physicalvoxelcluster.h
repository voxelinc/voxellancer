#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "collision/collision.h"
#include "property/property.h"
#include "worldtree/worldtreecluster.h"

class PhysicalVoxelCluster : public WorldTreeVoxelCluster {
public:
    PhysicalVoxelCluster(float scale = 1.0);
    PhysicalVoxelCluster(const PhysicalVoxelCluster & other);
    virtual ~PhysicalVoxelCluster();

    std::list<Collision> &move(float delta_sec);
    
    void accelerate(glm::vec3 direction);
    void accelerate_angular(glm::vec3 axis);

    virtual void addVoxel(const Voxel & voxel);
    virtual void removeVoxel(const cvec3 &position);

    virtual void finishInitialization();

protected:
    void calculateMassAndCenter();

    void handleCollision(Collision & c, float delta_sec);
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