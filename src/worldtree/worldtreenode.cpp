#include "worldtreenode.h"

#include <assert.h>
#include <algorithm>

#include "voxel/voxel.h"
#include "worldobject/worldobject.h"
#include "worldtreegeode.h"


static const int SUBNODE_COUNT = 8;

WorldTreeNode::WorldTreeNode(int octIndex, WorldTreeNode* parent, const IAABB& aabb):
    m_octIndex(octIndex),
    m_parent(parent),
    m_aabb(aabb),
    m_active(false)
{
    assert(m_aabb.extent(XAxis) == m_aabb.extent(YAxis) && m_aabb.extent(XAxis) == m_aabb.extent(ZAxis));
    m_extent = static_cast<float>(m_aabb.extent(ZAxis));
}

WorldTreeNode::WorldTreeNode(const IAABB &aabb, WorldTreeNode* initialSubnode):
    WorldTreeNode(0, nullptr, aabb)
{
    if (initialSubnode != nullptr) {
        convertToGroup(initialSubnode);
        initialSubnode->setParent(this);
    }
}

WorldTreeNode::~WorldTreeNode() {
    for (WorldTreeNode* subnode : m_subnodes) {
        delete subnode;
    }
}

void WorldTreeNode::clear() {
    assert(m_normalGeodes.empty());
    assert(m_passiveGeodes.empty());
    assert(m_activeSubnodes.empty());
    assert(!m_active);

    for (WorldTreeNode* subnode : m_subnodes) {
        delete subnode;
    }

    m_subnodes.clear();
    m_activeSubnodes.clear();
    m_passiveGeodes.clear();
}

int WorldTreeNode::octIndex() const {
    return m_octIndex;
}

void WorldTreeNode::setOctIndex(int octIndex) {
    m_octIndex = octIndex;
}

const IAABB &WorldTreeNode::aabb() const {
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

bool WorldTreeNode::active() const {
    return m_active;
}

void WorldTreeNode::setActive(bool active) {
    if (active != m_active) {
        m_active = active;

        if (m_parent != nullptr) {
            if(active) {
                m_parent->subnodeActivated(this);
            } else {
                m_parent->subnodeDeactivated(this);
            }
        }
    }
}

const std::list<WorldTreeGeode*>& WorldTreeNode::geodes() const {
    return m_normalGeodes;
}

const std::list<WorldTreeNode*>& WorldTreeNode::subnodes() const {
    return m_activeSubnodes;
}

bool WorldTreeNode::isLeaf() const {
    assert(!m_subnodes.empty() || m_activeSubnodes.empty());
    return m_subnodes.empty();
}

bool WorldTreeNode::isEmpty() const {
    return m_activeSubnodes.empty() && m_normalGeodes.empty() && m_passiveGeodes.empty();
}

bool WorldTreeNode::isRootnode() const {
    return m_parent == nullptr;
}

bool WorldTreeNode::isAtomic() const {
    return m_extent == MIN_EXTENT;
}

void WorldTreeNode::insert(WorldTreeGeode* geode) {
    assert(geode->aabb().intersects(m_aabb));

    if (m_aabb.contains(geode->aabb())) {
        geode->setContainingNode(this);
    }

    if(!m_active) {
        clear();
        assert(isLeaf());
    }

    std::list<WorldTreeGeode*>& geodes = geodesList(geode);

    if (isLeaf()) {
        if (std::find(geodes.begin(), geodes.end(), geode) == geodes.end()) {
            geodes.push_back(geode);
            geode->addIntersectingLeaf(this);
            setActive(true);

            if (m_normalGeodes.size() > MAX_GEODES && !isAtomic()) { // only active geodes are important for MAX_GEODES
                convertToGroup();
            }
        }
    } else {
        for (WorldTreeNode* subnode : m_subnodes) {
            if (subnode->aabb().intersects(geode->aabb())) {
                subnode->insert(geode);
                assert(!subnode->isEmpty());
            }
        }
    }
}

void WorldTreeNode::remove(WorldTreeGeode* geode) {
    if(isLeaf()) {
        geodesList(geode).remove(geode);

        if(isEmpty()) {
            setActive(false);
        }
    } else {
        assert(!m_activeSubnodes.empty());

        for (WorldTreeNode* subnode : m_subnodes) {
            if (subnode->active()) {
                subnode->remove(geode);
            }
        }
    }
}

void WorldTreeNode::convertToGroup(WorldTreeNode* initialSubnode) {
    assert(isLeaf());

    int subnodeExtent = static_cast<int>(m_extent / 2.0f);

    m_subnodes.resize(SUBNODE_COUNT);

    for(int n = 0; n < SUBNODE_COUNT; n++) {
        glm::ivec3 llf = glm::ivec3(n % 2, n/2 % 2, n/4) * subnodeExtent + m_aabb.llf();
        IAABB subnodeAABB(llf, llf + glm::ivec3(subnodeExtent));

        if (initialSubnode != nullptr && initialSubnode->aabb() == subnodeAABB) {
            m_subnodes[n] = initialSubnode;
            m_subnodes[n]->setOctIndex(n);
            if(initialSubnode->active()) {
                subnodeActivated(initialSubnode);
            }
        } else {
            m_subnodes[n] = new WorldTreeNode(n, this, subnodeAABB);
        }

        for (WorldTreeGeode* geode : m_normalGeodes) {
            if (geode->aabb().intersects(m_subnodes[n]->aabb())) {
                moveToSubnode(geode, m_subnodes[n]);
            }
        }
        for (WorldTreeGeode* geode : m_passiveGeodes) {
            if (geode->aabb().intersects(m_subnodes[n]->aabb())) {
                moveToSubnode(geode, m_subnodes[n]);
            }
        }
    }

    m_normalGeodes.clear();
    m_passiveGeodes.clear();

    assert(!isLeaf());
}

void WorldTreeNode::moveToSubnode(WorldTreeGeode* geode, WorldTreeNode* subnode) {
        subnode->insert(geode);
        geode->removeIntersectingLeaf(this);
}


void WorldTreeNode::subnodeActivated(WorldTreeNode* subnode) {
    m_activeSubnodes.push_back(subnode);
    setActive(true);
}

void WorldTreeNode::subnodeDeactivated(WorldTreeNode* subnode) {
    m_activeSubnodes.remove(subnode);

    if(m_activeSubnodes.empty()) {
        setActive(false);
    }
}

std::list<WorldTreeGeode*>& WorldTreeNode::geodesList(WorldTreeGeode* geode) {
    if (geode->isPassive()) {
        return m_passiveGeodes;
    } else {
        return m_normalGeodes;
    }
}
