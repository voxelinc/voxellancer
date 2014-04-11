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
    WorldTreeQuery(WorldTree* worldTree, WorldTreeNode* nodeHint = nullptr, CollisionFilter* collisionFilter = nullptr);
    WorldTreeQuery(WorldTree* worldTree, const AbstractShape* shape, WorldTreeNode* nodeHint = nullptr, CollisionFilter* collisionFilter = nullptr);

    const AbstractShape* shape() const;
    void setShape(const AbstractShape* shape);

    bool areGeodesNear();

    std::unordered_set<WorldTreeGeode*> nearGeodes();

    bool areVoxelsIntersecting();
    std::unordered_set<Voxel*> intersectingVoxels();

    std::unordered_set<WorldObject*> intersectingWorldObjects();

    WorldTreeNode* containingNode();


protected:
    WorldTree* m_worldTree;
    WorldTreeNode* m_nodeHint;
    CollisionFilter* m_collisionFilter;
    const AbstractShape* m_shape;
    WorldTreeNode* m_containingNode;
    bool m_queryInterrupted;

    WorldTreeNode* getQueryRoot() const;
    WorldTreeNode* getQueryRoot(WorldTreeNode* node) const;

    void startQuery(std::function<void(WorldTreeGeode*)> onGeodeInteraction);
    void query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction);
};

