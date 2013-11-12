#include "voxel.h"

#include <cassert>


Voxel::Voxel() :
    m_gridCell(0, 0, 0),
    m_color(1, 0, 1)
{
}

Voxel::Voxel(cvec3 gridCell, ucvec3 color) :
    m_gridCell(gridCell),
    m_color(color)
{
    assert(gridCell.x >= 0 && gridCell.y >= 0 && gridCell.z >= 0);
}

Voxel::~Voxel() {

}

const cvec3 &Voxel::gridCell() const {
    return m_gridCell;
}

void Voxel::setGridCell(const cvec3 &cell) {
    m_gridCell = cell;
}

const ucvec3 &Voxel::color() const {
    return m_color;
}

void Voxel::setColor(const ucvec3 &color) {
    m_color = color;
}

