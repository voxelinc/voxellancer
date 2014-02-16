#pragma once

#include <limits>
#include <string>

#include <glm/glm.hpp>

#include "property/property.h"


template<typename WorldObjectType>
WorldObjectType* WorldObjectBuilder::newWorldObject() {
	WorldObjectType* worldObject = new WorldObjectType();

	setupVoxelCluster(worldObject);
    setupComponents(worldObject->components());

    std::string collisionFieldOfDamageProperty = m_name + ".general.collisionFieldOfDamage";
    if (Property<std::string>(collisionFieldOfDamageProperty, "").get() == "inf") {
        worldObject->setCollisionFieldOfDamage(std::numeric_limits<float>::max());
    } else {
        worldObject->setCollisionFieldOfDamage(Property<float>(collisionFieldOfDamageProperty, glm::pi<float>() * 2));
    }

    return worldObject;
}

