#pragma once

#include <set>
#include <functional>


class WorldTree;
class WorldTreeNode;
class WorldTreeGeode;
class WorldObject;

template<typename Shape>
class WorldTreeQuery {
public:
    WorldTreeQuery(WorldTree* worldTree, const Shape& shape, WorldTreeNode* nodeHint = nullptr, WorldObject* collidableWith = nullptr);

    bool areGeodesIntersecting();
    std::set<WorldTreeGeode*> intersectingGeodes();

    bool areVoxelsIntersecting();
    std::set<Voxel*> intersectingVoxels();

    std::set<WorldObject*> intersectingWorldObjects();


protected:
    WorldTree* m_worldTree;
    WorldTreeNode* m_nodeHint;
    WorldTreeNode* m_startNode;
    WorldObject* m_collideableWith;
    Shape m_shape;
    bool m_queryInterrupted;

    WorldTreeNode* getQueryRoot(WorldTreeNode* node = nullptr) const;
    void query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeIntersection);
};


#include "worldtreequery.inl"
