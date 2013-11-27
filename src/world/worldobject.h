#include <memory>

#include "voxel/physicalvoxelcluster.h"

class WorldVoxel;

class WorldObject : public PhysicalVoxelCluster {
public:
    virtual void setWorldTree(Worldtree* worldTree);

    /* Idea to get around second list
    virtual void addVoxel(Voxel *voxel); // asserts that the voxel is a WorldVoxel, casts it to WorldVoxel and calls WorldVoxel::addToWorldObject(this)
    virtual void addVoxel(WorldVoxel *voxel); // adds the voxel
    WorldVoxel * voxel(cvec3 position); // does a static_cast to WorldVoxel, which is safe because addVoxel only accepts WorldVoxels
    */

protected:

private:    

};