#pragma once

#include <memory>

#include "utils/handle/handle.h"


class WorldTreeNode;


/**
 * Hidden twin of a WorldTreeNode, i.e. for every WorldTreeNode there is a
 * WorldTreeShadowNode.
 * This class is used by WorldTreeHints to find an undeleted and active WorldTreeNode
 * near to a location
 */
class WorldTreeShadowNode {
public:
    WorldTreeShadowNode(const std::shared_ptr<WorldTreeShadowNode>& parent, WorldTreeNode* node);

    WorldTreeShadowNode* parent();
    WorldTreeNode* node();


protected:
    bool m_parentRedirectActive;
    std::shared_ptr<WorldTreeShadowNode> m_parent;
    Handle<WorldTreeNode> m_node;
};

