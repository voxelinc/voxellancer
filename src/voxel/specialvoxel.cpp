#include "specialvoxel.h"


SpecialVoxel::SpecialVoxel(const glm::ivec3& cell, int group, uint32_t color, float mass, float hp):
    Voxel(cell, color, mass, hp),
    m_group(group)
{

}

int SpecialVoxel::group() const {
    return m_group;
}
