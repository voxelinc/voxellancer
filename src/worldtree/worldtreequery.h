#pragma once

#include <set>
#include <functional>


class WorldTreeNode;
class WorldTreeGeode;
class WorldObject;

template<typename Shape>
class WorldTreeQuery {
public:
    WorldTreeQuery(WorldTreeNode* worldTree, const Shape& shape, WorldTreeNode* nodeHint = nullptr, WorldObject* collidableWith = nullptr);

    bool areGeodesNear();
    std::set<WorldTreeGeode*> nearGeodes();

    bool areVoxelsIntersecting();
    std::set<Voxel*> intersectingVoxels();

    std::set<WorldObject*> intersectingWorldObjects();


protected:
    WorldTreeNode* m_worldTree;
    WorldTreeNode* m_nodeHint;
    WorldTreeNode* m_startNode;
    WorldObject* m_collideableWith;
    Shape m_shape;
    bool m_queryInterrupted;

    WorldTreeNode* getQueryRoot(WorldTreeNode* node = nullptr) const;
    void query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction);
};


#include "worldtreequery.inl"
