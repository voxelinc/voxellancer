#include "worldtreehint.h"

#include "worldtreeshadownode.h"


WorldTreeHint::WorldTreeHint(const std::shared_ptr<WorldTreeShadowNode>& shadowNode):
    m_shadowNode(shadowNode)
{
}

WorldTreeNode* WorldTreeHint::node() {
    return m_shadowNode.get() ? m_shadowNode->node() : nullptr;
}

