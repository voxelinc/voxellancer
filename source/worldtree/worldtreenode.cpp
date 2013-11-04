#include "worldtreenode.h"

#include <assert.h>
#include <algorithm>
#include <iostream>

#include "utils/tostring.h"


WorldtreeNode::WorldtreeNode(int level, WorldtreeNode *parent, const AABB &aabb):
    m_level(level),
    m_parent(parent),
    m_aabb(aabb)
{

}

WorldtreeNode::~WorldtreeNode() {
    for(WorldtreeNode *subnode : m_subnodes) {
        delete subnode;
    }
}

const AABB &WorldtreeNode::aabb() const {
    return m_aabb;
}

int WorldtreeNode::level() const {
    return m_level;
}

const std::list<WorldtreeGeode*> &WorldtreeNode::geodes() const {
    return m_geodes;
}

const std::list<WorldtreeNode*> &WorldtreeNode::subnodes() const {
    return m_subnodes;
}

WorldtreeNode *WorldtreeNode::parent() {
    return m_parent;
}

const WorldtreeNode *WorldtreeNode::parent() const {
    return m_parent;
}

bool WorldtreeNode::isLeaf() const {
    return m_subnodes.size() == 0;
}

bool WorldtreeNode::isRootnode() const {
    return m_parent == nullptr;
}

void WorldtreeNode::insert(WorldtreeGeode *geode) {
    if(m_aabb.contains(geode->aabb())) {
        geode->setContainingNode(this);
    }

    if(isRootnode()) {
        if(!m_aabb.contains(geode->aabb())) {
            octuple(geode->aabb());
            insert(geode);
            return;
        }
    }

    if(isLeaf()) {
        m_geodes.push_back(geode);
        if(m_geodes.size() > MAX_GEODES && m_level < MAX_DEPTH) {
            split();
        }
    }
    else {
        for(WorldtreeNode *subnode : m_subnodes) {
            if(subnode->aabb().intersects(geode->aabb())) {
                subnode->insert(geode);
            }
        }
    }
}

void WorldtreeNode::remove(WorldtreeGeode *geode) {
    if(isLeaf()) {
        std::list<WorldtreeGeode*>::iterator i = std::find(m_geodes.begin(), m_geodes.end(), geode);
        if(i != m_geodes.end()) {
            m_geodes.erase(i);
        }
    }
    else {
        for(WorldtreeNode *subnode : m_subnodes) {
            subnode->remove(geode);
        }
    }
}

std::set<WorldtreeGeode*> WorldtreeNode::geodesInAABB(const AABB &aabb) const {
    std::set<WorldtreeGeode*> result;

    if(isLeaf()) {
        for(WorldtreeGeode *geode : m_geodes) {
            if(aabb.intersects(geode->aabb())) {
                result.insert(geode);
            }
        }
    }
    else {
        for(WorldtreeNode *subnode : m_subnodes) {
            if(aabb.intersects(subnode->aabb())) {
                std::set<WorldtreeGeode*> subresult = subnode->geodesInAABB(aabb);
                result.insert(subresult.begin(), subresult.end());
            }
        }
    }

    return result;
}


void WorldtreeNode::aabbChanged(WorldtreeGeode *geode) {
    if(m_aabb.contains(geode->aabb())) {
        remove(geode);
        insert(geode);
    }
    else {
        if(isRootnode()) {
            octuple(geode->aabb());
            aabbChanged(geode);
            return;
        }
        else {
            m_parent->aabbChanged(geode);
        }
    }
}

void WorldtreeNode::split() {
    assert(isLeaf());

    std::list<AABB> aabbs = m_aabb.recursiveSplit(2, XAxis);

    for(AABB &aabb : aabbs) {
        m_subnodes.push_back(new WorldtreeNode(m_level+1, this, aabb));
    }

    for(WorldtreeNode *subnode : m_subnodes) {
        for(WorldtreeGeode *geode : m_geodes) {
            if(subnode->aabb().intersects(geode->aabb())) {
                subnode->insert(geode);
            }
        }
    }
}

void WorldtreeNode::unsplit() {
    assert(!isLeaf());

    for(WorldtreeNode *subnode : m_subnodes) {
        assert(subnode->isLeaf());

        for(WorldtreeGeode *geode : subnode->m_geodes) {
            if(geode->containingNode() == subnode) {
                geode->setContainingNode(this);
            }
            m_geodes.push_back(geode);
        }
        delete subnode;
    }

    m_subnodes.clear();
}

void WorldtreeNode::octuple(const AABB &aabb) {
    WorldtreeNode *oldThis = new WorldtreeNode(m_level+1, this, m_aabb);
    oldThis->m_geodes.splice(oldThis->m_geodes.end(), m_geodes);
    oldThis->m_subnodes.splice(oldThis->m_subnodes.end(), m_subnodes);

    for(WorldtreeGeode *geode : oldThis->m_geodes) {
        if(geode->containingNode() == this) {
            geode->setContainingNode(oldThis);
        }
    }

    m_subnodes.clear();
    m_geodes.clear();

    m_subnodes.push_back(oldThis);

    for(int a = 0; a < 3; a++) {
        Axis axis = (Axis)a;
        int extentDir = aabb.axisMin(axis) <= m_aabb.axisMin(axis) ? -1 : 1;

        std::list<WorldtreeNode*> mirroredSubnodes;
        for(WorldtreeNode *subnode : m_subnodes) {
            WorldtreeNode *mirroredNode = new WorldtreeNode(m_level+1, this, subnode->aabb().moved(axis, extentDir * subnode->aabb().extent(axis)));
            mirroredSubnodes.push_back(mirroredNode);
        }
        m_subnodes.splice(m_subnodes.end(), mirroredSubnodes);

        m_aabb.expand(axis, extentDir * m_aabb.extent(axis));
    }
}

