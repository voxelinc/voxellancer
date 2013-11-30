#include <list>

#include "collision/collisiondetector.h"
#include "physics/physics.h"
#include "world/drawable.h"
#include "voxel/voxelcluster.h"
#include "world/drawable.h"

class WorldObject : public Drawable
{
public:
    WorldObject(float scale = 1.0f);
    virtual ~WorldObject();

    CollisionDetector * collisionDetector();
    Physics* physics();
    VoxelCluster* voxelCluster();

    AABB aabb();
    Sphere sphere();

    virtual void update(float delta_sec);

    virtual std::list<Collision>& move(float delta_sec);

    void addVoxel(Voxel * voxel);
    void removeVoxel(const glm::ivec3 & position);
    void finishInitialization();

    Voxel *crucialVoxel();

    WorldTransform & transform();

    void accelerate(glm::vec3 direction);
    void accelerateAngular(glm::vec3 axis);

protected:
    CollisionDetector m_collisionDetector;
    Physics m_physics;
    VoxelCluster m_voxelCluster;
    WorldTransform m_transform;
};
