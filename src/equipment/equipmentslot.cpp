#include "equipmentslot.h"


EquipmentSlot::EquipmentSlot(WorldObjectComponents* components, int group):
    m_components(components),
    m_group(group)
{
}

EquipmentSlot::~EquipmentSlot() = default;

std::list<std::string> EquipmentSlot::mountables() const {
    std::list<std::string> result;
    for(std::map<std::string, bool>::const_iterator i = m_mountables.begin(); i != m_mountables.end(); ++i) {
        if(i->second) {
            result.push_back(i->first);
        }
    }
    return result;
}

bool EquipmentSlot::mountable(const std::string& name) const {
    std::map<std::string, bool>::const_iterator i = m_mountables.find(name);
    return i == m_mountables.end() ? false : i->second;
}

void EquipmentSlot::setMountable(const std::string& name, bool mountable) {
    m_mountables[name] = mountable;
}

WorldObjectComponents* EquipmentSlot::components() {
    return m_components;
}

const WorldObjectComponents* EquipmentSlot::components() const {
    return m_components;
}

int EquipmentSlot::group() const {
    return m_group;
}

