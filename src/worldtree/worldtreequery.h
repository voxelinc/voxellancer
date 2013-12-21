#pragma once

#include <set>


class WorldTree;
class WorldTreeNode;
class WorldTreeGeode;
class WorldObject;

template<typename Shape>
class WorldTreeQuery {
    WorldTreeQuery(WorldTree* worldTree, const Shape& shape);

    void setNodeHint(WorldTreeNode* nodeHint);
    void setCollideableWith(WorldObject* worldObject)

    bool areGeodesIntersecting(const Shape& shape) const;
    std::set<WorldTreeGeode*> intersectingGeodes(const Shape& shape) const;

    bool areVoxelsIntersecting(const Shape& shape) const;
    std::set<Voxel*> intersectingVoxels(const Shape& shape) const;

    bool areWorldObjectsIntersecting(const Shape& shape) const;
    std::set<Voxel*> intersectingVoxels(const Shape& shape) const;


protected:
    WorldTree* m_worldTree;
    WorldTreeNode* m_nodeHint;
    WorldObject* m_collideableWith;
    Shape m_shape;
};


#include "worldtreequery.inl"
