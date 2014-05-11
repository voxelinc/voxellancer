#pragma once

#include <list>
#include <set>
#include <vector>

#include "geometry/aabb.h"

#include "utils/handle/handleowner.h"

#include "worldtreehint.h"


class WorldTreeGeode;
class WorldTreeNode;

class WorldTreeNode : public HandleOwner {
public:
    WorldTreeNode(int octIndex, WorldTreeNode* parent, const IAABB &aabb);
    WorldTreeNode(const IAABB &aabb, WorldTreeNode* initialSubnode);
    virtual ~WorldTreeNode();

    void clear();

    int octIndex() const;
    void setOctIndex(int octIndex);

    const IAABB& aabb() const;

    WorldTreeNode *parent();
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

    WorldTreeHint hint();


protected:
    static const int MIN_EXTENT = 16;
    static const int MAX_GEODES = 8;

    WorldTreeNode* m_parent;
    IAABB m_aabb;
    int m_octIndex;
    float m_extent;
    bool m_active;

    std::list<WorldTreeGeode*> m_normalGeodes;
    std::list<WorldTreeGeode*> m_passiveGeodes;
    std::vector<WorldTreeNode*> m_subnodes;
    std::list<WorldTreeNode*> m_activeSubnodes;

    std::shared_ptr<WorldTreeShadowNode> m_shadowNode;


    /**
     * Convert a leaf to a node with subnodes
     */
    void convertToGroup(WorldTreeNode* initialSubnode = nullptr);

    /**
     * Move a geode to the specified subnode if it is contained in its aabb
     */
    void moveToSubnode(WorldTreeGeode* geode, WorldTreeNode* subnode);

    void subnodeActivated(WorldTreeNode* subnode);
    void subnodeDeactivated(WorldTreeNode* subnode);

    std::list<WorldTreeGeode*>& geodesList(WorldTreeGeode* geode);

};

