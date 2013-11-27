#include "voxel/voxelcluster.h"

class CollisionDetector;

// this class contains datastructures for collision detection
class CollidableVoxelCluster : public VoxelCluster {

public:
    CollidableVoxelCluster(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    virtual ~CollidableVoxelCluster();

    virtual void addVoxel(Voxel *voxel);
    virtual void removeVoxel(const cvec3 &position);

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);
    void setWorldTree(Worldtree* worldTree);
    Worldtree* worldTree();

    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

    virtual void finishInitialization();
    void updateGeode();
protected:
    VoxeltreeNode m_voxelTree;
    WorldtreeGeode *m_geode;
    Worldtree *m_worldTree;
    std::unique_ptr<CollisionDetector> m_collisionDetector;

};