#include "jumpgateloader.h"

#include <glm/gtc/quaternion.hpp>


JumpgateLoader::JumpgateLoader(const std::string& group):
    m_group(group)
    m_loaded(false)
    m_buddy(0)
{
}

JumpgateLoader::~JumpgateLoader() = default;

Jumpgate* JumpgateLoader::jumpgate() {
    loadLazy();
    return m_jumpgate;
}

const std::string& JumpgateLoader::targetSector() {
    loadLazy();
    return m_targetSector;
}

int JumpgateLoader::buddy() {
    loadLazy();
    return m_buddy;
}

void JumpgateLoader:loadLazy() {
    if (m_loaded) {
        return;
    }

    m_jumpgate = WorldObjectBuilder("jumpgate").buildJumpgate();
    jumpgate->transform().setPosition(Property<glm::vec3>::get(m_group + ".position"));
    jumpgate->transform().setOrientation(glm::quat(Property<glm::vec3>::get(m_group + ".orientation", glm::vec3(0.0f))));

    m_targetSector = Property<std::string>::get(m_group + ".target");
    m_buddy = Property<int>(m_group + ".buddy");

    m_loaded = true;
}

