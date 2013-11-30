
#include <glm/glm.hpp>

class VoxelCluster;


class Drawable {

public:
    virtual VoxelCluster * voxelCluster() = 0;
    virtual glm::mat4 matrix() = 0;

};