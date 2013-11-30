#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "collision/collision.h"

#include "property/property.h"

#include "voxel/voxelcluster.h"


class CollisionDetector;

class PhysicalVoxelCluster : public VoxelCluster
{
public:
    PhysicalVoxelCluster(float scale = 1.0);
    virtual ~PhysicalVoxelCluster();

    WorldTreeGeode *geode();
    const WorldTreeGeode *geode() const;
    void setGeode(WorldTreeGeode *geode);
    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();

    VoxelTreeNode &voxeltree();
    const VoxelTreeNode &voxeltree() const;

    std::list<Collision> &move(float delta_sec);

    void accelerate(glm::vec3 direction);
    void accelerateAngular(glm::vec3 axis);

    virtual void addVoxel(Voxel *voxel);
    virtual void removeVoxel(const cvec3 &position);
    std::list<PhysicalVoxel*> &physicalVoxels();
    const std::list<PhysicalVoxel*> &physicalVoxels() const;


    virtual void finishInitialization();
    void updateGeode();


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

    VoxelTreeNode m_voxelTree;
    WorldTreeGeode *m_geode;
    WorldTree *m_worldTree;

    WorldTransform m_oldTransform;
    WorldTransform m_newTransform;

    glm::vec3 m_speed;
    glm::vec3 m_angularSpeed;

    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;

    Property<float> m_dampening;
    Property<float> m_angularDampening;
    Property<float> m_rotationFactor;

    std::list<PhysicalVoxel*> m_physicalVoxels;
};
