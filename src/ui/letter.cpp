#include "ui/letter.h"

Letter::Letter(float scale):
    VoxelCluster(scale)
{

}

void Letter::setCenter(glm::vec3 center) {
    m_transform.setCenter(center);
}

void Letter::setScale(float scale) {
    m_transform.setScale(scale);
}


