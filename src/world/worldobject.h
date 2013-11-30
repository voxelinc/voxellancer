#include <list>

#include "collision/collisiondetector.h"
#include "physics/physics.h"
#include "world/drawable.h"
#include "voxel/voxelcluster.h"


class WorldObject : public Drawable
{
public:
    CollisionDetector * collisionDetector();
    Physics * physics();
    VoxelCluster * voxelCluster();

    AABB aabb();
    Sphere sphere();

    virtual void update(float delta_sec);
    virtual void move(float delta_sec);
    void updateGeode();

    void addVoxel(Voxel * voxel);
    void removeVoxel(const cvec3 & position);

    virtual glm::mat4 matrix();
    bool transform();

    void accelerate(glm::vec3 direction);
    void accelerateAngular(glm::vec3 axis);


protected:
    CollisionDetector m_collisionDetector;
    Physics m_physics;
    VoxelCluster m_voxelCluster;
};
