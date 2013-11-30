
#include <glm/glm.hpp>

class VoxelCluster;
class WorldTransform;

class Drawable {

public:
    virtual VoxelCluster * voxelCluster() = 0;
    virtual WorldTransform& transform() = 0;

};