#pragma once

#include <set>


class WorldTree;
class WorldTreeNode;
class WorldTreeGeode;
class WorldObject;

template<typename Shape>
class WorldTreeQuery {
    WorldTreeQuery(WorldTree* worldTree);

    void setNodeHint(WorldTreeNode* nodeHint);
    void setCollideableWith(WorldObject* worldObject)


    bool areGeodesIntersecting() const;
    std::set<WorldTreeGeode*> intersectingGeodes() const;

    bool areVoxelsIntersecting() const;
    std::set<Voxel*> intersectingVoxels() const;

    bool areWorldObjectsIntersecting() const;
    std::set<Voxel*> intersectingVoxels() const;


protected:
    WorldTree* m_worldTree;
    WorldTreeNode* m_nodeHint;
    WorldObject* m_collideableWith;
};


#include "worldtreequery.inl"
