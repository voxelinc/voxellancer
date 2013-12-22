#pragma once

#include <functional>
#include <cassert>

#include <worldtree/worldtree.h>
#include <worldtree/worldtreenode.h>
#include <worldtree/worldtreegeode.h>
#include <worldobject/worldobject.h>

#include "voxel/voxeltreequery.h"


template<typename Shape>
WorldTreeQuery<Shape>::WorldTreeQuery(WorldTreeNode* worldTree, const Shape& shape, WorldTreeNode* nodeHint, WorldObject* collidableWith):
    m_worldTree(worldTree),
    m_nodeHint(nodeHint),
    m_collideableWith(collidableWith),
    m_shape(shape),
    m_queryInterrupted(false)
{
}

template<typename Shape>
bool WorldTreeQuery<Shape>::areGeodesNear() {
    bool result = false;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        result = true;
        m_queryInterrupted = true;
    });

    return result;
}

template<typename Shape>
std::set<WorldTreeGeode*> WorldTreeQuery<Shape>::nearGeodes() {
    std::set<WorldTreeGeode*>  result;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        result.insert(geode);
    });

    return result;
}

template<typename Shape>
bool WorldTreeQuery<Shape>::areVoxelsIntersecting() {
    bool result = false;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        VoxelTreeQuery<Shape> voxelTreeQuery(&geode->worldObject()->collisionDetector().voxeltree(), m_shape);

        if(voxelTreeQuery.areVoxelsIntersecting()) {
            result = true;
            m_queryInterrupted = true;
        }
    });

    return result;
}

template<typename Shape>
std::set<Voxel*> WorldTreeQuery<Shape>::intersectingVoxels() {
    std::set<Voxel*> result;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        VoxelTreeQuery<Shape> voxelTreeQuery(&geode->worldObject()->collisionDetector().voxeltree(), m_shape);

        std::set<Voxel*> subresult = voxelTreeQuery.intersectingVoxels();
        result.insert(subresult.begin(), subresult.end());
    });

    return result;
}

template<typename Shape>
std::set<WorldObject*> WorldTreeQuery<Shape>::intersectingWorldObjects() {
    std::set<WorldObject*> result;
    m_queryInterrupted = false;

    query(getQueryRoot(), [&](WorldTreeGeode* geode) {
        VoxelTreeQuery<Shape> voxelTreeQuery(&geode->worldObject()->collisionDetector().voxeltree(), m_shape);

        bool hasIntersectingVoxels = voxelTreeQuery.areVoxelsIntersecting();
        if(hasIntersectingVoxels) {
            result.insert(geode->worldObject());
        }
    });

    return result;
}

template<typename Shape>
WorldTreeNode* WorldTreeQuery<Shape>::getQueryRoot(WorldTreeNode* node) const {
    if(node == nullptr) {
        node = m_nodeHint;
    }

    if (node == nullptr) {
        return m_worldTree;
    }
    else {
        if (node->aabb().contains(m_shape)) {
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

template<typename Shape>
void WorldTreeQuery<Shape>::query(WorldTreeNode* node, std::function<void(WorldTreeGeode*)> onGeodeInteraction) {
    if(node->isLeaf()) {
        for(WorldTreeGeode* geode : node->geodes()) {
            assert(geode->aabb().intersects(node->aabb()));
            assert(geode->worldObject() != nullptr);

            if(m_collideableWith == nullptr || m_collideableWith->isCollideableWith(geode->worldObject())) {
                if(m_shape.nearTo(geode->aabb())) {
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
            if(m_shape.nearTo(subnode->aabb())) {
                query(subnode, onGeodeInteraction);

                if(m_queryInterrupted) {
                    return;
                }
            }
        }
    }
}

