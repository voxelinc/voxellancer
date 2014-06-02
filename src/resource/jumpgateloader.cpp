#include "jumpgateloader.h"

#include <glm/gtc/quaternion.hpp>

#include "property/property.h"

#include "worldobjectbuilder.h"


JumpgateLoader::JumpgateLoader(const std::string& group):
    m_group(group),
    m_loaded(false),
    m_buddy(0)
{
    std::cout << "GRoup " << m_group << std::endl;
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

void JumpgateLoader::loadLazy() {
    if (m_loaded) {
        return;
    }

    m_jumpgate = WorldObjectBuilder("jumpgate").buildJumpgate();
    m_jumpgate->transform().setPosition(Property<glm::vec3>::get(m_group + ".position"));
    m_jumpgate->transform().setOrientation(glm::quat(Property<glm::vec3>::get(m_group + ".orientation", glm::vec3(0.0f))));

    m_targetSector = Property<std::string>::get(m_group + ".targetSector");
    m_buddy = Property<int>(m_group + ".buddy");

    m_loaded = true;
}

