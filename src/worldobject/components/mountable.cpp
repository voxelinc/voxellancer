#include "mountable.h"

bool Mountable::mountable(const std::string& name) const {
    std::map<std::string, bool>::const_iterator i = m_mountables.find(name);
    return i == m_mountables.end() ? false : i->second;
}

void Mountable::setMountable(const std::string& name, bool mountable) {
    m_mountables[name] = mountable;
}

