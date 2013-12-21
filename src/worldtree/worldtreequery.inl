#pragma once

#include <cassert>

#include <worldtree/worldtree.h>
#include <worldtree/worldtreenode.h>
#include <worldtree/worldtreegeode.h>
#include <worldobject/worldobject.h>


template<typename Shape>
WorldTreeQuery<Shape>::WorldTreeQuery(WorldTree* worldTree, const Shape& shape):
    m_worldTree(worldTree),
    m_nodeHint(nullptr),
    m_collideableWith(nullptr),
    m_shape(shape)
{

}

template<typename Shape>
void WorldTreeQuery<Shape>::setNodeHint(WorldTreeNode* nodeHint) {
    m_nodeHint = nodeHint;
}

template<typename Shape>
void WorldTreeQuery<Shape>::setCollidableWith(WorldObject* worldObject) {
    m_collideableWith = worldObject;
}

template<typename Shape>
bool WorldTreeQuery<Shape>::areGeodesIntersecting() const {
    if (m_nodeHint == nullptr) {
        return areGeodesIntersecting(m_worldTree);
    }
    else {
        if (m_nodeHint->aabb().contains(m_shape)) {
            return areGeodesIntersecting(m_nodeHint);
        }Ŕ
        else if(m_nodeHint->parent() != nullptr) {
            m_nodeHint = m_nodeHint->parent()
            return areGeodesIntersecting();
        }
        else {
            assert(m_worldTree == m_nodeHint);
            return areGeodesIntersecting(m_worldTree);
        }
    }
}

template<typename Shape>
std::set<WorldTreeGeode*> WorldTreeQuery<Shape>::intersectingGeodes() const {

}

template<typename Shape>
bool WorldTreeQuery<Shape>::areVoxelsIntersecting() const {

}

template<typename Shape>
std::set<Voxel*> WorldTreeQuery<Shape>::intersectingVoxels() const {

}

template<typename Shape>
bool WorldTreeQuery<Shape>::areWorldObjectsIntersecting() const {

}

template<typename Shape>
std::set<Voxel*> WorldTreeQuery<Shape>::intersectingVoxels() const {

}

