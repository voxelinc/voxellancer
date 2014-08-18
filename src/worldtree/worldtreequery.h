#pragma once

#include <functional>
#include <unordered_set>
#include <set>

#include "worldtreehint.h"


class AbstractShape;
class CollisionFilter;
class Voxel;
class WorldObject;
class WorldTree;
class WorldTreeNode;
class WorldTreeGeode;

class WorldTreeQuery {
public:
    WorldTreeQuery(WorldTree* worldTree, const WorldTreeHint& hint = WorldTreeHint(), const CollisionFilter* collisionFilter = nullptr);
    WorldTreeQuery(WorldTree* worldTree, const AbstractShape* shape, const WorldTreeHint& hint = WorldTreeHint(), const CollisionFilter* collisionFilter = nullptr);

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
    WorldTreeHint m_hint;
    const CollisionFilter* m_collisionFilter;
    const AbstractShape* m_shape;
    WorldTreeNode* m_containingNode;
    bool m_queryInterrupted;

    WorldTreeNode* getQueryRoot() const;
    WorldTreeNode* getQueryRoot(WorldTreeNode* node) const;

    void startQuery(std::function<void(WorldTreeGeode*)> onGeodeInteraction);
    void query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction);
};

