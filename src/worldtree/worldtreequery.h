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
    WorldTreeQuery(WorldTree* worldTree, const AbstractShape* shape, const WorldTreeHint& hint = WorldTreeHint(), CollisionFilter* collisionFilter = nullptr);

    bool areGeodesNear();

    std::unordered_set<WorldTreeGeode*> nearGeodes();

    bool areVoxelsIntersecting();
    std::unordered_set<Voxel*> intersectingVoxels();

    std::unordered_set<WorldObject*> intersectingWorldObjects();


protected:
    WorldTree* m_worldTree;
    WorldTreeHint m_hint;
    CollisionFilter* m_collisionFilter;
    const AbstractShape* m_shape;
    bool m_queryInterrupted;

    WorldTreeNode* getQueryRoot(WorldTreeNode* node = nullptr) const;
    void query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction);
};

