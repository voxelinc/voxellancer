#include "voxel.h"


Voxel::Voxel() :
    m_position(0.0f, 0.0f, 0.0f),
    m_color(1.0f, 0.0f, 1.0f)
{

}

Voxel::Voxel(cvec3 position, ucvec3 color) :
    m_position(position),
    m_color(color)
{

}

Voxel::~Voxel() {

}

const glm::ivec3 &Voxel::gridCell() {
    return m_gridCell;
}

void Voxel::setGridCell(const glm::ivec3 &cell) {
    m_gridCell = cell;
}

const cvec3 & Voxel::position() const
{
    return m_position;
}

const ucvec3 & Voxel::color() const
{
    return m_color;
}

