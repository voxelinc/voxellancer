#include "specialvoxel.h"


SpecialVoxel::SpecialVoxel(const glm::ivec3& gridCell, int group, uint32_t color, float mass, float hp):
    Voxel(gridCell, color, mass, hp),
    m_group(group)
{

}

int SpecialVoxel::group() const {
    return m_group;
}

SpecialVoxel* SpecialVoxel::clone() const {
    return new SpecialVoxel(*this);
}

