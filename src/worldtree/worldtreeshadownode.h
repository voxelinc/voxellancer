#pragma once

#include <memory>


class WorldTreeNode;

enum WorldTreeShadowNodeState
{
    Active,
    Inactive,
    Zombie
};

/**
 * Hidden twin of a WorldTreeNode, that means that for every WorldTreeNode there is a
 * WorldTreeShadowNode.
 * This class is used by WorldTreeHints to find an undeleted and active WorldTreeNode
 */
class WorldTreeShadowNode {
public:
    WorldTreeShadowNode(const std::shared_ptr<WorldTreeShadowNode>& parent, WorldTreeNode* node);

    WorldTreeShadowNode* parent();
    WorldTreeNode* node();


protected:
    WorldTreeShadowNodeImpl m_impl;
};

