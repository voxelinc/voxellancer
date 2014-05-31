#include "propertynode.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>


PropertyNode::PropertyNode()
{
}

PropertyNode::PropertyNode(const std::string& name):
    m_name(name)
{
}

const std::string& PropertyNode::name() const {
    return m_name;
}

std::vector<std::string> PropertyNode::childrenNames() const {
    std::vector<std::string> result;

    for (auto pair : m_children) {
        result.push_back(pair.first);
    }

    return result;
}

void PropertyNode::insert(const std::vector<std::string>& path) {
    if (path.empty()) {
        return;
    }

    auto iter = m_children.find(path[0]);

    if (iter == m_children.end()) {
        auto node = std::make_shared<PropertyNode>(path[0]);
        iter = m_children.emplace(path[0], node).first;
    }

    iter->second->insert(std::vector<std::string>(path.begin() + 1, path.end()));
}

const PropertyNode* PropertyNode::find(const std::vector<std::string>& path) const {
    if (path.empty()) {
        return this;
    }

    auto iter = m_children.find(path[0]);

    if (iter == m_children.end()) {
        return nullptr;
    } else {
        return iter->second->find(std::vector<std::string>(path.begin() + 1, path.end()));
    }
}

bool PropertyNode::pathExists(const std::vector<std::string>& path) const {
    if (path.empty()) {
        return true;       
    }

    auto iter = m_children.find(path[0]);

    if (iter == m_children.end()) {
        return false;
    } else {
        return iter->second->pathExists(std::vector<std::string>(path.begin() + 1, path.end()));
    }
}


