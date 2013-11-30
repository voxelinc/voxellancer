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


protected:
    CollisionDetector m_collisionDetector;
    Physics m_physics;
    VoxelCluster m_voxelCluster;

private:

};

