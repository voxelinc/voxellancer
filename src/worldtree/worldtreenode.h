#pragma once

#include <list>
#include <set>

#include "worldtreegeode.h"
#include "geometry/aabb.h"


class WorldTreeNode
{
public:
    WorldTreeNode(int octIndex, WorldTreeNode* parent, const AABB &aabb, WorldTreeNode* initialSubnode);
    virtual ~WorldTreeNode();

    int octIndex() const;
    void setOctIndex(int octIndex);

    const AABB& aabb() const;

    WorldTreeNode *parent();
    const WorldTreeNode *parent() const;
    void setParent(WorldTreeNode *parent);

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
    AABB m_aabb;
    int m_octIndex;
    float m_extent;

    std::list<WorldTreeGeode*> m_geodes;
    std::list<WorldTreeNode*> m_exposedSubnodes;
    std::vector<WorldTreeNode*> m_subnodes;
    std::vector<bool> m_subnodeExposed;

    void toGroup();
    void toLeaf();
    void expose(int octIndex, bool exposed);
};

