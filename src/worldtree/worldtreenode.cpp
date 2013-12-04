#include "worldtreenode.h"

#include <assert.h>
#include <algorithm>
#include <iostream>

#include "utils/tostring.h"


WorldTreeNode::WorldTreeNode(int level, WorldTreeNode *parent, const AABB &aabb):
    m_level(level),
    m_parent(parent),
    m_aabb(aabb)
{

}

WorldTreeNode::~WorldTreeNode() {
    for(WorldTreeNode *subnode : m_subnodes) {
        delete subnode;
    }
}

const AABB &WorldTreeNode::aabb() const {
    return m_aabb;
}

int WorldTreeNode::level() const {
    return m_level;
}

const std::list<WorldTreeGeode*> &WorldTreeNode::geodes() const {
    return m_geodes;
}

const std::list<WorldTreeNode*> &WorldTreeNode::subnodes() const {
    return m_subnodes;
}

WorldTreeNode *WorldTreeNode::parent() {
    return m_parent;
}

const WorldTreeNode *WorldTreeNode::parent() const {
    return m_parent;
}

bool WorldTreeNode::isLeaf() const {
    return m_subnodes.size() == 0;
}

bool WorldTreeNode::isRootnode() const {
    return m_parent == nullptr;
}

void WorldTreeNode::insert(WorldTreeGeode *geode) {
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
        for(WorldTreeNode *subnode : m_subnodes) {
            if(subnode->aabb().intersects(geode->aabb())) {
                subnode->insert(geode);
            }
        }
    }
}

void WorldTreeNode::remove(WorldTreeGeode *geode) {
    if(isLeaf()) {
        std::list<WorldTreeGeode*>::iterator i = std::find(m_geodes.begin(), m_geodes.end(), geode);
        if(i != m_geodes.end()) {
            m_geodes.erase(i);
        }
    }
    else {
        for(WorldTreeNode *subnode : m_subnodes) {
            subnode->remove(geode);
        }
    }
}

std::set<WorldTreeGeode*> WorldTreeNode::geodesInAABB(const AABB &aabb) const {
    std::set<WorldTreeGeode*> result;

    if(isLeaf()) {
        for(WorldTreeGeode *geode : m_geodes) {
            if(aabb.intersects(geode->aabb())) {
                result.insert(geode);
            }
        }
    }
    else {
        for(WorldTreeNode *subnode : m_subnodes) {
            if(aabb.intersects(subnode->aabb())) {
                std::set<WorldTreeGeode*> subresult = subnode->geodesInAABB(aabb);
                result.insert(subresult.begin(), subresult.end());
            }
        }
    }

    return result;
}


void WorldTreeNode::aabbChanged(WorldTreeGeode *geode) {
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

void WorldTreeNode::poll(int& nodes, int &empty, int& geodes, int& depth) {
    if(isLeaf() && m_geodes.size() == 0) {
        empty++;
    }

    nodes++;
    geodes += m_geodes.size();
    depth = std::max(depth, m_level);

    for(auto subnode : m_subnodes) {
        subnode->poll(nodes, empty, geodes, depth);
    }
}

void WorldTreeNode::print() {
    auto indent = [&] {
        for(int i = 0; i < m_level; i++) {
            std::cout << "  ";
        }
    };

    indent(); std::cout << m_level << ": " << toString(m_aabb) << std::endl;

    for(WorldTreeGeode* geode : m_geodes) {
        indent(); std::cout << "  Geode " << toString(geode->aabb()) << std::endl;
    }

    for(WorldTreeNode* subnode : m_subnodes) {
        subnode->print();
    }
}

void WorldTreeNode::split() {
    assert(isLeaf());

    std::list<AABB> aabbs = m_aabb.recursiveSplit(2, XAxis);

    for(AABB &aabb : aabbs) {
        m_subnodes.push_back(new WorldTreeNode(m_level+1, this, aabb));
    }

    for(WorldTreeNode *subnode : m_subnodes) {
        for(WorldTreeGeode *geode : m_geodes) {
            if(subnode->aabb().intersects(geode->aabb())) {
                subnode->insert(geode);
            }
        }
    }
}

void WorldTreeNode::unsplit() {
    assert(!isLeaf());

    for(WorldTreeNode *subnode : m_subnodes) {
        assert(subnode->isLeaf());

        for(WorldTreeGeode *geode : subnode->m_geodes) {
            if(geode->containingNode() == subnode) {
                geode->setContainingNode(this);
            }
            m_geodes.push_back(geode);
        }
        delete subnode;
    }

    m_subnodes.clear();
}

void WorldTreeNode::octuple(const AABB &aabb) {
    assert(m_level == 0);

    WorldTreeNode *oldThis = new WorldTreeNode(m_level+1, this, m_aabb);
    oldThis->m_geodes.splice(oldThis->m_geodes.end(), m_geodes);
    oldThis->m_subnodes.splice(oldThis->m_subnodes.end(), m_subnodes);

    for(WorldTreeGeode *geode : oldThis->m_geodes) {
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

        std::list<WorldTreeNode*> mirroredSubnodes;
        for(WorldTreeNode *subnode : m_subnodes) {
            WorldTreeNode *mirroredNode = new WorldTreeNode(m_level+1, this, subnode->aabb().moved(axis, extentDir * subnode->aabb().extent(axis)));
            mirroredSubnodes.push_back(mirroredNode);
        }
        m_subnodes.splice(m_subnodes.end(), mirroredSubnodes);

        m_aabb.expand(axis, extentDir * m_aabb.extent(axis));
    }

    for(WorldTreeNode* subnode : m_subnodes) {
        subnode->setLevel(1);
    }
}

void WorldTreeNode::setLevel(int level) {
    m_level = level;
    for(WorldTreeNode* subnode : m_subnodes) {
        subnode->setLevel(level + 1);
    }
}

