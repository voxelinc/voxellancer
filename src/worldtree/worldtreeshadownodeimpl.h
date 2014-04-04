#pragma once


class WorldTreeShadowNodeImpl {
public:
    WorldTreeShadowNodeImpl(const std::shared_ptr<WorldTreeShadowNode>& parent, WorldTreeNode* node);


};

    std::shared_ptr<WorldTreeShadowNode> m_parent;
    WorldTreeNode* m_node;
