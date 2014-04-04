#pragma once

#include <memory>

#include "utils/handle/handle.h"

#include "worldtreeshadownode.h"


class WorldTreeShadowNodeImpl {
public:
    WorldTreeShadowNodeImpl(const std::shared_ptr<WorldTreeShadowNode>& parent, WorldTreeNode* node);

    WorldTreeShadowNode* parent();
    WorldTreeNode* node();

    bool parentRedirectActive() const;
    void setParentRedirectActive(bool active);


protected:
    bool m_parentRedirectActive;
    std::shared_ptr<WorldTreeShadowNode> m_parent;
    Handle<WorldTreeNode> m_node;
};

