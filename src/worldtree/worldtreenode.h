#pragma once

#include <list>
#include <set>
#include <vector>

#include "geometry/aabb.h"


class WorldTreeGeode;
class WorldTreeNode;

class WorldTreeNode
{
public:
    WorldTreeNode(int octIndex, WorldTreeNode* parent, const IAABB &aabb);
    WorldTreeNode(const IAABB &aabb, WorldTreeNode* initialSubnode);
    virtual ~WorldTreeNode();

    void clear();

    int octIndex() const;
    void setOctIndex(int octIndex);

    const IAABB& aabb() const;

    WorldTreeNode *parent();
    const WorldTreeNode *parent() const;
    void setParent(WorldTreeNode *parent);

    bool active() const;
    void setActive(bool active);

    const std::list<WorldTreeGeode*>& geodes() const;
    const std::list<WorldTreeNode*>& subnodes() const;

    bool isLeaf() const;
    bool isEmpty() const;
    bool isRootnode() const;
    bool isAtomic() const;

    void insert(WorldTreeGeode* geode);
    void remove(WorldTreeGeode* geode);


protected:
    static const int MIN_EXTENT = 16;
    static const int MAX_GEODES = 4;

    WorldTreeNode* m_parent;
    IAABB m_aabb;
    int m_octIndex;
    float m_extent;
    bool m_active;

    std::list<WorldTreeGeode*> m_geodes;
    std::vector<WorldTreeNode*> m_subnodes;
    std::list<WorldTreeNode*> m_activeSubnodes;

    void toGroup(WorldTreeNode* initialSubnode = nullptr);

    void subnodeActivated(WorldTreeNode* subnode);
    void subnodeDeactivated(WorldTreeNode* subnode);
};

