#include "voxel.h"

Voxel::Voxel() {

}

Voxel::~Voxel() {

}


const glm::ivec3 &Voxel::gridCell() {
    return m_gridCell;
}

void Voxel::setGridCell(const glm::ivec3 &cell) {
    m_gridCell = cell;
}

