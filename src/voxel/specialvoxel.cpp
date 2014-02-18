#include "specialvoxel.h"


SpecialVoxel::SpecialVoxel(const glm::ivec3& gridCell, int index, int color, float mass, float hp):
    Voxel(gridCell, color, mass, hp),
    m_index(index)
{

}

int SpecialVoxel::index() const {
    return m_index;
}
