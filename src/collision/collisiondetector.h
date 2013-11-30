#include <memory>

#include <glm/glm.hpp>

#include "voxel/voxel.h"
#include "voxel/voxeltreenode.h"
#include "collision/collision.h"

class WorldTree;
class WorldTreeGeode;
class WorldObject;


// this class contains datastructures for collision detection
class CollisionDetector
{
public:
    CollisionDetector(WorldObject & worldObject);
    virtual ~CollisionDetector();

    virtual void addVoxel(Voxel *voxel);
    virtual void removeVoxel(const cvec3 &position);

    std::list<Collision> &checkCollisions();
    std::list<Collision> &lastCollisions();
    void reset();

    WorldTreeGeode *geode();
    const WorldTreeGeode *geode() const;
    void setGeode(WorldTreeGeode *geode);
    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();

    VoxelTreeNode &voxeltree();
    const VoxelTreeNode &voxeltree() const;

    void updateGeode();
        
    virtual void finishInitialization();


protected:
    void checkCollisions(VoxelTreeNode* nodeA, VoxelTreeNode* nodeB, WorldObject *  other);

    WorldObject & m_worldObject;
    VoxelTreeNode m_voxelTree;
    WorldTreeGeode *m_geode;
    WorldTree *m_worldTree;
    std::list<Collision> m_collisions;
};
