#include "worldtreeshadownode.h"

#include "worldtreenode.h"


WorldTreeShadowNode::WorldTreeShadowNode(const std::shared_ptr<WorldTreeShadowNode>& parent, WorldTreeNode* node):
    m_parentRedirectActive(nullptr),
    m_parent(parent),
    m_node(node->handle<WorldTreeNode>())
{
}

WorldTreeShadowNode* WorldTreeShadowNode::parent() {
    return m_parent.get();
}

WorldTreeNode* WorldTreeShadowNode::node() {
    if (m_node.valid() && m_node->active()) {
        return m_node.get();
    } else {
        return m_parent ? m_parent->node() : nullptr;
    }
}

