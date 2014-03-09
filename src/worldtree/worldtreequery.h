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


protected:
    WorldTree* m_worldTree;
    WorldTreeNode* m_nodeHint;
    CollisionFilter* m_collisionFilter;
    const AbstractShape* m_shape;
    bool m_queryInterrupted;

    WorldTreeNode* getQueryRoot(WorldTreeNode* node = nullptr) const;
    void query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction);
};
