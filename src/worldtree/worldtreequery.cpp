#include "worldtreequery.h"

#include <functional>
#include <cassert>

#include "collision/collisionfilterable.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreenode.h"
#include "worldtree/worldtreegeode.h"

#include "worldobject/worldobject.h"

#include "voxel/voxel.h"
#include "voxel/voxeltreequery.h"



WorldTreeQuery::WorldTreeQuery(WorldTree* worldTree, const AbstractShape* shape, WorldTreeNode* nodeHint, CollisionFilterable* collisionFilter):
    m_worldTree(worldTree),
    m_nodeHint(nodeHint),
    m_collisionFilter(collisionFilter),
    m_shape(shape),
    m_queryInterrupted(false)
{

}

bool WorldTreeQuery::areGeodesNear() {
    bool result = false;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        result = true;
        m_queryInterrupted = true;
    });

    return result;
}

std::set<WorldTreeGeode*> WorldTreeQuery::nearGeodes() {
    std::set<WorldTreeGeode*>  result;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        result.insert(geode);
    });

    return result;
}

bool WorldTreeQuery::areVoxelsIntersecting() {
    bool result = false;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        VoxelTreeQuery voxelTreeQuery(&geode->worldObject()->collisionDetector().voxelTree(), m_shape);

        if(voxelTreeQuery.areVoxelsIntersecting()) {
            result = true;
            m_queryInterrupted = true;
        }
    });

    return result;
}

std::set<Voxel*> WorldTreeQuery::intersectingVoxels() {
    std::set<Voxel*> result;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        VoxelTreeQuery voxelTreeQuery(&geode->worldObject()->collisionDetector().voxelTree(), m_shape);

        std::set<Voxel*> subresult = voxelTreeQuery.intersectingVoxels();
        result.insert(subresult.begin(), subresult.end());
    });

    return result;
}

std::set<WorldObject*> WorldTreeQuery::intersectingWorldObjects() {
    std::set<WorldObject*> result;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        VoxelTreeQuery voxelTreeQuery(&geode->worldObject()->collisionDetector().voxelTree(), m_shape);

        bool hasIntersectingVoxels = voxelTreeQuery.areVoxelsIntersecting();
        if(hasIntersectingVoxels) {
            result.insert(geode->worldObject());
        }
    });

    return result;
}

WorldTreeNode* WorldTreeQuery::getQueryRoot(WorldTreeNode* node) const {
    if(node == nullptr) {
        node = m_nodeHint;
    }

    if (node == nullptr) {
        return m_worldTree->root();
    }
    else {
        if (m_shape->containedBy(node->aabb())) {
            return node;
        }
        else if (node->parent() != nullptr) {
            node = node->parent();
            return getQueryRoot(node);
        }
        else {
            return m_worldTree->root();
        }
    }
}

void WorldTreeQuery::query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction) {
    if(node->isLeaf()) {
        assert(!node->geodes().empty());
        for(WorldTreeGeode* geode : node->geodes()) {
            assert(geode->aabb().intersects(node->aabb()));
            assert(geode->worldObject() != nullptr);

            if(m_collisionFilter == nullptr || m_collisionFilter->isCollideableWith(geode->worldObject())) {
                if(m_shape->nearTo(geode->aabb())) {
                    onGeodeInteraction(geode);

                    if(m_queryInterrupted) {
                        return;
                    }
                }
            }
        }
    }
    else {
        for(WorldTreeNode* subnode : node->subnodes()) {
            if(m_shape->nearTo(subnode->aabb())) {
                query(subnode, onGeodeInteraction);

                if(m_queryInterrupted) {
                    return;
                }
            }
        }
    }
}

