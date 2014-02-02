#include "worldobjectslot.h"

#include <iostream>


WorldObjectSlot::WorldObjectSlot(WorldObjectComponents* components, int index):
    m_components(components),
    m_index(index)
{
}

bool WorldObjectSlot::mountable(const std::string& name) const {
    std::map<std::string, bool>::const_iterator i = m_mountables.find(name);
    return i == m_mountables.end() ? false : i->second;
}

void WorldObjectSlot::setMountable(const std::string& name, bool mountable) {
    std::cout << "Mountable " << name << " = " << mountable << std::endl;
    m_mountables[name] = mountable;
}

WorldObjectComponents* WorldObjectSlot::components() {
    return m_components;
}

int WorldObjectSlot::index() const {
    return m_index;
}

