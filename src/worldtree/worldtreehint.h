#pragma once

#include <memory>


class WorldTreeNode;
class WorldTreeShadowNode;

/**
 * Returns the deepest active and undeleted node starting from the WorldTreeNode
 * it was obtained from
 */
class WorldTreeHint {
public:
    WorldTreeHint(const std::shared_ptr<WorldTreeShadowNode>& shadowNode);

    WorldTreeNode* node();


protected:
    std::shared_ptr<WorldTreeShadowNode> m_shadowNode;
};

