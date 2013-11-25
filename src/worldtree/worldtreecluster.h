#include "voxel/voxelcluster.h"

// this class contains datastructures for collision detection
class WorldTreeVoxelCluster : public VoxelCluster {

public:
    WorldTreeVoxelCluster(glm::vec3 center = glm::vec3(0), float scale = 1.0);
    WorldTreeVoxelCluster(const WorldTreeVoxelCluster& other);
    virtual ~WorldTreeVoxelCluster();

    virtual void addVoxel(const Voxel & voxel);
    virtual void removeVoxel(const cvec3 &position);

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);
    void setWorldTree(Worldtree* worldTree);

    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

    virtual void finishInitialization();
    void updateGeode();
protected:

    VoxeltreeNode m_voxelTree;
    WorldtreeGeode *m_geode;
    Worldtree *m_worldTree;

};