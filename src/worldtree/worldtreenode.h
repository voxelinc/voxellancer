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
class WorldtreeNode
{
public:
    WorldtreeNode(int level, WorldtreeNode *parent, const AABB &aabb);
    WorldtreeNode(const WorldtreeNode &other);
    virtual ~WorldtreeNode();

    const AABB &aabb() const;

    int level() const;

    const std::list<WorldtreeGeode*> &geodes() const;
    const std::list<WorldtreeNode*> &subnodes() const;

    WorldtreeNode *parent();
    const WorldtreeNode *parent() const;

    bool isLeaf() const;
    bool isRootnode() const;

    void insert(WorldtreeGeode *geode);
    void remove(WorldtreeGeode *geode);

    std::set<WorldtreeGeode*> geodesInAABB(const AABB &aabb) const;

    void aabbChanged(WorldtreeGeode *geode);


protected:
    static const int MAX_DEPTH = 8;
    static const int MAX_GEODES = 8;

    friend class WorldtreeCleaner;

    WorldtreeNode *m_parent;
    AABB m_aabb;
    int m_level;
    std::list<WorldtreeGeode*> m_geodes;
    std::list<WorldtreeNode*> m_subnodes;

    void split();
    void unsplit();
    void octuple(const AABB &aabb);
};

