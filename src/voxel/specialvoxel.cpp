#include "specialvoxel.h"


SpecialVoxel::SpecialVoxel(const glm::ivec3& gridCell, int index, uint32_t color, float mass, float hp):
    Voxel(gridCell, color, mass, hp),
    m_index(index)
{

}

int SpecialVoxel::index() const {
    return m_index;
}
