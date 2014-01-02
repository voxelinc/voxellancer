#include "worldtreenode.h"

#include <assert.h>
#include <algorithm>
#include <iostream>

#include "utils/tostring.h"
#include "voxel/voxel.h"
#include "worldobject/worldobject.h"


static const int SUBNODE_COUNT = 8;

WorldTreeNode::WorldTreeNode(int octIndex, WorldTreeNode* parent, const AABB& aabb, WorldTreeNode* initialSubnode):
    m_octIndex(octIndex),
    m_parent(parent),
    m_aabb(aabb)
{
    assert(m_aabb.extent(XAxis) == m_aabb.extent(YAxis) && m_aabb.extent(XAxis) == m_aabb.extent(ZAxis));
    m_extent = m_aabb.extent(ZAxis);

    if(initialSubnode != nullptr) {
        toGroup();
        for(int n = 0; n < SUBNODE_COUNT; n++) { // TODO: shrink iteration range
            WorldTreeNode* subnode = m_subnodes[n];

            if(initialSubnode->aabb() == subnode->aabb()) {
                delete subnode;
                m_subnodes[n] = initialSubnode;
            }
        }
        initialSubnode->setParent(this);
    }
}

WorldTreeNode::~WorldTreeNode() {
    for(WorldTreeNode* subnode : m_subnodes) {
        delete subnode;
    }
}

int WorldTreeNode::octIndex() const {
    return m_octIndex;
}

void WorldTreeNode::setOctIndex(int octIndex) {
    m_octIndex = octIndex;
}

const AABB &WorldTreeNode::aabb() const {
    return m_aabb;
}

WorldTreeNode* WorldTreeNode::parent() {
    return m_parent;
}

const WorldTreeNode* WorldTreeNode::parent() const {
    return m_parent;
}

void WorldTreeNode::setParent(WorldTreeNode* parent) {
    assert(m_parent == nullptr);
    m_parent = parent;
}

const std::list<WorldTreeGeode*>& WorldTreeNode::geodes() const {
    return m_geodes;
}

const std::list<WorldTreeNode*>& WorldTreeNode::subnodes() const {
    return m_exposedSubnodes;
}

bool WorldTreeNode::isLeaf() const {
    assert(!m_subnodes.empty() || m_exposedSubnodes.empty());
    return m_subnodes.empty();
}

bool WorldTreeNode::isEmpty() const {
    return m_exposedSubnodes.empty() && m_geodes.empty();
}

bool WorldTreeNode::isRootnode() const {
    return m_parent == nullptr;
}

bool WorldTreeNode::isAtomic() const {
    return m_extent == MIN_EXTENT;
}

void WorldTreeNode::insert(WorldTreeGeode* geode) {
    assert(geode->aabb().intersects(m_aabb));

    if(m_aabb.contains(geode->aabb())) {
        geode->setContainingNode(this);
    }

    if(isLeaf()) {
        if(std::find(m_geodes.begin(), m_geodes.end(), geode) == m_geodes.end()) {
            m_geodes.push_back(geode);
            geode->addIntersectingLeaf(this);
            if(m_geodes.size() > MAX_GEODES && !isAtomic()) {
                toGroup();
            }
        }
    }
    else {
        for(int n = 0; n < SUBNODE_COUNT; n++) { // TODO: shrink iteration range
            WorldTreeNode* subnode = m_subnodes[n];

            if(subnode->aabb().intersects(geode->aabb())) {
                subnode->insert(geode);

                if(!m_subnodeExposed[n]) {
                    expose(n, true);
                }
            }
        }
    }
}

void WorldTreeNode::remove(WorldTreeGeode* geode) {
    if(isLeaf()) {
        m_geodes.remove(geode);
    }
    else {
        assert(!m_exposedSubnodes.empty());

        for(int n = 0; n < SUBNODE_COUNT; n++) { // TODO: shrink iteration range
            WorldTreeNode* subnode = m_subnodes[n];

            bool emptyBefore = subnode->isEmpty();

            subnode->remove(geode);

            if(subnode->isEmpty() && !emptyBefore) {
                assert(m_subnodeExposed[n]);
                expose(n, false);
            }
        }

        if(m_exposedSubnodes.empty()) {
            toLeaf();
        }
    }
}


void WorldTreeNode::toGroup() {
    assert(isLeaf());

    float subnodeExtent = m_extent / 2.0f;

    m_subnodes.resize(SUBNODE_COUNT);
    m_subnodeExposed.resize(SUBNODE_COUNT, false);

    for(int n = 0; n < SUBNODE_COUNT; n++) {
        glm::vec3 llf = glm::vec3(n % 2, n/2 % 2, n/4) * subnodeExtent + m_aabb.llf();
        AABB subnodeAABB(llf, llf + glm::vec3(subnodeExtent));

        m_subnodes[n] = new WorldTreeNode(n, this, subnodeAABB, nullptr);

        for(WorldTreeGeode* geode : m_geodes) {
            if(geode->aabb().intersects(m_subnodes[n]->aabb())) {
                m_subnodes[n]->insert(geode);
                if(!m_subnodeExposed[n]) {
                    expose(n, true);
                }
            }
        }
    }

    for(WorldTreeGeode* geode : m_geodes) {
        geode->removeIntersectingLeaf(this);
    }
    m_geodes.clear();

    assert(!isLeaf());
}

void WorldTreeNode::toLeaf() {
    assert(!isLeaf());

    for(WorldTreeNode* subnode : m_subnodes) {
        assert(subnode->isLeaf());
        assert(subnode->geodes().empty());
        delete subnode;
    }

    m_subnodes.clear();
    m_exposedSubnodes.clear();
    m_subnodeExposed.clear();

    assert(isLeaf());
}

void WorldTreeNode::expose(int octIndex, bool exposed) {
    assert(m_subnodeExposed[octIndex] != exposed);

    WorldTreeNode* subnode = m_subnodes[octIndex];

    if(exposed) {
        m_exposedSubnodes.push_back(subnode);
    } else {
        m_exposedSubnodes.remove(subnode);
    }

    m_subnodeExposed[octIndex] = exposed;
}

