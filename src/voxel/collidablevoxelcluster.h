#include "voxel/voxelcluster.h"

class CollisionDetector;

// this class contains datastructures for collision detection
class CollidableVoxelCluster : public VoxelCluster {

public:
    CollidableVoxelCluster(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    virtual ~CollidableVoxelCluster();

    virtual void addVoxel(Voxel *voxel);
    virtual void removeVoxel(const cvec3 &position);

    WorldTreeGeode *geode();
    const WorldTreeGeode *geode() const;
    void setGeode(WorldTreeGeode *geode);
    void setWorldTree(WorldTree* worldTree);
    WorldTree* worldTree();

    VoxelTreeNode &voxeltree();
    const VoxelTreeNode &voxeltree() const;

    virtual void finishInitialization();
    void updateGeode();
protected:
    VoxelTreeNode m_voxelTree;
    WorldTreeGeode *m_geode;
    WorldTree *m_worldTree;
    std::unique_ptr<CollisionDetector> m_collisionDetector;

};