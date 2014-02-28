#pragma once

#include <functional>
#include <unordered_set>
#include <set>

class Voxel;
class WorldTree;
class WorldTreeNode;
class WorldTreeGeode;
class WorldObject;
class CollisionFilter;
class AbstractShape;

class WorldTreeQuery {
public:
    WorldTreeQuery(WorldTree* worldTree, const AbstractShape* shape, WorldTreeNode* nodeHint = nullptr, CollisionFilter* collisionFilter = nullptr);

    bool areGeodesNear();

    std::unordered_set<WorldTreeGeode*> nearGeodes();

    bool areVoxelsIntersecting();
    std::unordered_set<Voxel*> intersectingVoxels();

    std::unordered_set<WorldObject*> intersectingWorldObjects();

    /*
        The last visited node, can be used as a hint for the next query with a similar
        shape
    */
    WorldTreeNode* lastNode();


protected:
    WorldTree* m_worldTree;
    WorldTreeNode* m_nodeHint;
    WorldTreeNode* m_startNode;
    WorldTreeNode* m_lastNode;
    CollisionFilter* m_collisionFilter;
    const AbstractShape* m_shape;
    bool m_queryInterrupted;

    WorldTreeNode* getQueryRoot(WorldTreeNode* node = nullptr) const;
    void query(WorldTreeNode* node, const std::function<void(WorldTreeGeode*)>& onGeodeInteraction);
};
