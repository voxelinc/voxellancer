#include "worldtreequery.h"

#include <functional>
#include <cassert>

#include <worldtree/worldtree.h>

#include <worldtree/worldtreenode.h>
#include <worldtree/worldtreegeode.h>
#include <worldobject/worldobject.h>

#include "voxel/voxel.h"
#include "voxel/voxeltreequery.h"



WorldTreeQuery::WorldTreeQuery(WorldTreeNode* worldTree, const AbstractShape* shape, WorldTreeNode* nodeHint, WorldObject* collidableWith):
    m_worldTree(worldTree),
    m_nodeHint(nodeHint),
    m_collideableWith(collidableWith),
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
        VoxelTreeQuery voxelTreeQuery(&geode->worldObject()->collisionDetector().voxeltree(), m_shape);

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
        VoxelTreeQuery voxelTreeQuery(&geode->worldObject()->collisionDetector().voxeltree(), m_shape);

        std::set<Voxel*> subresult = voxelTreeQuery.intersectingVoxels();
        result.insert(subresult.begin(), subresult.end());
    });

    return result;
}

std::set<WorldObject*> WorldTreeQuery::intersectingWorldObjects() {
    std::set<WorldObject*> result;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        VoxelTreeQuery voxelTreeQuery(&geode->worldObject()->collisionDetector().voxeltree(), m_shape);

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
        return m_worldTree;
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
            return m_worldTree;
        }
    }
}

void WorldTreeQuery::query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction) {
    if(node->isLeaf()) {
        for(WorldTreeGeode* geode : node->geodes()) {
            assert(geode->aabb().intersects(node->aabb()));
            assert(geode->worldObject() != nullptr);

            if(m_collideableWith == nullptr || m_collideableWith->isCollideableWith(geode->worldObject())) {
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
        for(WorldTreeNode *subnode : node->subnodes()) {
            if(m_shape->nearTo(subnode->aabb())) {
                query(subnode, onGeodeInteraction);

                if(m_queryInterrupted) {
                    return;
                }
            }
        }
    }
}
