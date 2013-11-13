#pragma once

#include <glm/glm.hpp>
#include "geometry/sphere.h"


typedef glm::detail::tvec3<signed char> cvec3;
typedef glm::detail::tvec3<unsigned char> ucvec3;

struct VoxelHash
{
    std::size_t operator()(const cvec3& v) const {
        return v.x + (v.y << 8) + (v.z << 16);
    }
};


class VoxelCluster;

class Voxel
{
public:
    Voxel(VoxelCluster *voxelCluster = nullptr);
    Voxel(cvec3 gridCell, ucvec3 color, VoxelCluster *voxelCluster = nullptr);
    virtual ~Voxel();

    VoxelCluster *voxelCluster();
    const VoxelCluster *voxelCluster() const;

    const cvec3 &gridCell() const;
    void setGridCell(const cvec3 &cell);

    const ucvec3 &color() const;
    void setColor(const ucvec3 &color);


protected:
    VoxelCluster *m_voxelCluster;
    cvec3 m_gridCell;
    ucvec3 m_color;
};

