#include "voxel.h"



Voxel::Voxel() : 
    m_position(),
    m_color()
{

}

Voxel::Voxel(cvec3 position, ucvec3 color) :
    m_position(position),
    m_color(color)
{

}

Voxel::~Voxel()
{

}

const cvec3 & Voxel::position() const
{
    return m_position;
}

const ucvec3 & Voxel::color() const
{
    return m_color;
}
