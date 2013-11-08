#pragma once

#include <glm/glm.hpp>

typedef glm::detail::tvec3<signed char> cvec3;
typedef glm::detail::tvec3<unsigned char> ucvec3;

struct VoxelHash
{
    std::size_t operator()(const cvec3& v) const {
        return v.x + (v.y << 8) + (v.z << 16);
    }
};

class Voxel
{
public:
    Voxel();
    Voxel(cvec3 position, ucvec3 color);
    virtual ~Voxel();

    const cvec3 & position() const;
    const ucvec3 & color() const;

protected:
    cvec3 m_position;
    ucvec3 m_color;

};
