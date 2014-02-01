#include "worldobjectcomponent.h"


WorldObjectComponent::WorldObjectComponent(WorldObjectComponents* components, const std::string& name, int index):
    m_components(components),
    m_name(name),
    m_index(index)
{
}

WorldObjectComponents* WorldObjectComponents::components() {
    return m_components;
}

const std::string& WorldObjectComponents::name() {
    return m_name;
}

int WorldObjectComponent::index() {
    return m_index;
}

