#pragma once

#include <list>
#include <set>

#include "worldtreegeode.h"
#include "../geometry/aabb.h"

/*!
    remove() doesn't unsplit. This could happen recursive upwards the tree,
    which is unclean since subnodes would have to order their parents to delete them.

    unsplitting should happen regulary by a different entity, maybe using tokens, that
    mark changed nodes
*/
class WorldTreeNode
{
public:
    WorldTreeNode(int level, WorldTreeNode *parent, const AABB &aabb);
    WorldTreeNode(const WorldTreeNode &other);
    virtual ~WorldTreeNode();

    const AABB &aabb() const;

    int level() const;

    const std::list<WorldTreeGeode*> &geodes() const;
    const std::list<WorldTreeNode*> &subnodes() const;

    WorldTreeNode *parent();
    const WorldTreeNode *parent() const;

    bool isLeaf() const;
    bool isRootnode() const;

    void insert(WorldTreeGeode *geode);
    void remove(WorldTreeGeode *geode);

    std::set<WorldTreeGeode*> geodesInAABB(const AABB &aabb) const;
    bool areGeodesInAABB(const AABB &aabb) const;

    void aabbChanged(WorldTreeGeode *geode);

    void poll(int& nodes, int &empty, int& geodes, int& depth);
    void print();


protected:
    static const int MIN_EXTENT = 16;
    static const int MAX_GEODES = 4;

    friend class WorldTreeCleaner;

    WorldTreeNode *m_parent;
    AABB m_aabb;
    int m_level;
    int m_extent;
    std::list<WorldTreeGeode*> m_geodes;
    std::list<WorldTreeNode*> m_subnodes;

    void split();
    void unsplit();
    void octuple(const AABB &aabb);
    void setLevel(int level);
};

