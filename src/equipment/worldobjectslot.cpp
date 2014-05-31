#include "worldobjectslot.h"


WorldObjectSlot::WorldObjectSlot(WorldObjectComponents* components, int group):
    m_components(components),
    m_group(group)
{
}

WorldObjectSlot::~WorldObjectSlot() = default;

std::list<std::string> WorldObjectSlot::mountables() const {
    std::list<std::string> result;
    for(std::map<std::string, bool>::const_iterator i = m_mountables.begin(); i != m_mountables.end(); ++i) {
        if(i->second) {
            result.push_back(i->first);
        }
    }
    return result;
}

bool WorldObjectSlot::mountable(const std::string& name) const {
    std::map<std::string, bool>::const_iterator i = m_mountables.find(name);
    return i == m_mountables.end() ? false : i->second;
}

void WorldObjectSlot::setMountable(const std::string& name, bool mountable) {
    m_mountables[name] = mountable;
}

WorldObjectComponents* WorldObjectSlot::components() {
    return m_components;
}

const WorldObjectComponents* WorldObjectSlot::components() const {
    return m_components;
}

int WorldObjectSlot::group() const {
    return m_group;
}

