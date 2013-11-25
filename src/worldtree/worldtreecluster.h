#include "voxel/voxelcluster.h"

// this class contains datastructures for collision detection
class WorldTreeCluster : public VoxelCluster {

public:
    WorldTreeCluster(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    WorldTreeCluster(const WorldTreeCluster& other);
    virtual ~WorldTreeCluster();

    virtual void addVoxel(const Voxel & voxel);
    virtual void removeVoxel(const cvec3 &position);

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);
    void setWorldTree(Worldtree* worldTree);

    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

protected:
    void updateGeode();

    VoxeltreeNode m_voxelTree;
    WorldtreeGeode *m_geode;
    Worldtree *m_worldTree;

};