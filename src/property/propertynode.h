#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


class PropertyNode final {
public:
    PropertyNode();
    PropertyNode(const std::string& name);

    const std::string& name() const;

    std::vector<std::string> childrenNames() const;

    void insert(const std::vector<std::string>& path);
    const PropertyNode* find(const std::vector<std::string>& path) const;
    bool pathExists(const std::vector<std::string>& path) const;


protected:
    std::string m_name;
    std::unordered_map<std::string, std::shared_ptr<PropertyNode>> m_children;
};

