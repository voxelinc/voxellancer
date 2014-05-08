#include "worldtreehint.h"

#include "worldtreenode.h"
#include "worldtreeshadownode.h"


WorldTreeHint::WorldTreeHint(WorldTreeNode* node):
    m_shadowNode(node ? node->hint().m_shadowNode : nullptr)
{
}

WorldTreeHint::WorldTreeHint(const std::shared_ptr<WorldTreeShadowNode>& shadowNode):
    m_shadowNode(shadowNode)
{
}

WorldTreeNode* WorldTreeHint::node() const {
    return m_shadowNode.get() ? m_shadowNode->node() : nullptr;
}

