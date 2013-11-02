#include "worldtreenode.h"
#include <assert.h>
#include <algorithm>

WorldtreeNode::WorldtreeNode(int level, WorldtreeNode *parent, const AABB &aabb):
    m_level(level),
    m_parent(parent),
    m_aabb(aabb),
    m_totalNumGeodes(0)
{

}

virtual WorldtreeNode::~WorldtreeNode() {
    for(WorldtreeNode *subnode : m_subnodes) {
        delete subnode;
    }
}

const AABB &WorldtreeNode::aabb() const {
    return m_aabb;
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
    return parent == nullptr;
}

void WorldtreeNode::insert(WorldtreeGeode *geode) {
    if(m_aabb.contains(geode->aabb())) {
        geode->setContainingNode(geode);
    }

    if(isLeaf()) {
        if(isRootnode()) {
            if(!m_aabb.contains(geode->aabb())) {
                octuple(geode->aabb());
                insert(geode);
                return;
            }
        }

        m_geodes.push_back(geode);
        if(m_geodes.size() > MAX_GEODES && m_level < MAX_LEVEL) {
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

    m_totalNumGeodes++;
}

bool WorldtreeNode::remove(WorldtreeGeode *geode) {
    if(isLeaf()) {
        std::list<WorldtreeGeode>::iterator i = std::find(m_geodes.begin(), m_geodes.end(), geode);
        if(i != m_geodes.end()) {
            m_geodes.erase(i);
            m_totalNumGeodes--;
            return true;
        }
    }
    else {
        bool removedFromSubnode = false;

        for(WorldtreeNode *subnode : m_subnodes) {
            removedFromSubnode |= subnode->remove(geode);
        }

        if(removedFromSubnode) {
            m_totalNumGeodes--;

            if(m_totalNumGeodes <= MAX_GEODES) {
                unsplit();
            }
        }
    }
}

std::set<WorldtreeGeode*> WorldtreeNode::geodesInAABB(const AABB &aabb) {
    std::set<WorltreeGeode*> result;

    if(isLeaf()) {
        for(WorldtreeGeode *geode : m_geodes) {
            if(aabb.intersects(geode->aabb())) {
                result.insert(geode);
            }
        }
    }
    else {
        for(WorldTreeNode *subnode : m_subnodes) {
            if(aabb.intersects(subnode->aabb())) {
                std::set<WorldtreeGeode> subresult = subnode->geodesInAABB(aabb);
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
            parent->aabbChanged(geode);
        }
    }
}

void WorldtreeNode::split() {
    assert(isLeaf());

    std::list<AABB> aabbs = m_aabb.recursiveSplit(3, AABB::SplitX);

    for(AABB &aabb : aabbs) {
        m_subnodes.push_back(new WorldtreeNode(m_level+1, this, aabb));
    }

    for(WorldtreeNode *subnode : m_subnodes) {
        for(WorldtreeGeode *geode : m_geode) {
            if(subnode->aabb().intersectes(geode->aabb())) {
                subnode->insert(geode);
            }
        }
    }
}

void WorldtreeNode::unsplit() {
    assert(!isLeaf());
    assert(m_totalNumGeodes <= MAX_GEODES);

    for(WorldtreeNode *subnode : m_subnodes) {
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

    m_subnodes.clear();
    m_geodes.clear();

    m_subnodes.push_back(oldThis);

    if(aabb.right() <= m_aabb.left()) {
        m_subnodes.push_back(new WorldtreeNode(m_level+1, this, m_aabb.movedLeft(m_aabb.width())));
    }
    else {
        m_subnodes.push_back(new WorldtreeNode(m_level+1, this, m_aabb.movedRight(m_aabb.width())));
    }

    std::list<WorldtreeNode*> newSubnodes;
    for(WorldtreeNode *subnode : m_subnodes) {
        if(aabb.back() <= m_aabb.front()) {
            newSubnodes.push_back(new WorldtreeNode(m_level+1, this, subnode->aabb().movedFront(subnode->aabb().depth())));
        }
        else {
            newSubnodes.push_back(new WorldtreeNode(m_level+1, this, subnode->aabb().movedBack(subnode->aabb().depth())));
        }
    }
    m_subnodes.splice(m_subnodes.end(), newSubnodes);

    newSubnodes.clear();
    for(WorldtreeNode *subnode : m_subnodes) {
        if(aabb.top() <= m_aabb.bottom()) {
            newSubnodes.push_back(new WorldtreeNode(m_level+1, this, subnode->aabb().movedDown(subnode->aabb().depth())));
        }
        else {
            newSubnodes.push_back(new WorldtreeNode(m_level+1, this, subnode->aabb().movedUp(subnode->aabb().depth())));
        }
    }
    m_subnodes.splice(m_subnodes.end(), newSubnodes);
}


