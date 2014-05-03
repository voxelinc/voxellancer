#pragma once

#include <memory>


class WorldTreeNode;
class WorldTreeShadowNode;

/**
 * Returns the deepest active and undeleted node starting from the WorldTreeNode
 * it was obtained from.
 */
class WorldTreeHint {
public:
    WorldTreeHint(WorldTreeNode* node = nullptr);

    /**
     * This constructor shouldn't be called by the user directly.
     * Instead use WorldTreeNode::hint() to acquire a WorldTreeHint
     */
    WorldTreeHint(const std::shared_ptr<WorldTreeShadowNode>& shadowNode);

    WorldTreeNode* node() const;


protected:
    std::shared_ptr<WorldTreeShadowNode> m_shadowNode;
};

