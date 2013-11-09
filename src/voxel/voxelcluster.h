#pragma once

#include <glm/glm.hpp>

#include "voxeltreenode.h"

#include "worldtransform.h"

#include "geometry/aabb.h"


class WorldtreeGeode;

class Voxelcluster
{
public:
    Voxelcluster();
    virtual ~Voxelcluster();

    const AABB &aabb();

    VoxeltreeNode &voxeltree();
    const VoxeltreeNode &voxeltree() const;

    WorldtreeGeode *geode();
    const WorldtreeGeode *geode() const;
    void setGeode(WorldtreeGeode *geode);

protected:
    glm::vec3 m_rotationCenter;
    WorldTransform m_worldTransform;
    AABB m_aabb;
    VoxeltreeNode m_voxeltree;
    WorldtreeGeode *m_geode;
};

