#include "worldobjectbuilder.h"

#include <cassert>

#include <glow/logging.h>

#include "worldobject/genericship.h"
#include "worldobject/genericworldobject.h"
#include "worldobject/ship.h"
#include "worldobject/weapons/genericbullet.h"
#include "worldobject/weapons/genericrocket.h"
#include "worldobject/worldobject.h"


WorldObjectBuilder::WorldObjectBuilder(const std::string& name):
    m_name(name)
{
}

WorldObject* WorldObjectBuilder::build() {
    std::string type = Property<std::string>(m_name + ".general.type");

    if(type == "bullet") {
        return buildBullet();
    } else if(type == "rocket") {
        return buildRocket();
    } else if(type == "ship") {
        return buildShip();
    } else if(type == "other") {
        return buildWorldObject();
    } else {
        glow::fatal("Unknown WorldObject-Type '%;'", type);
    }
    assert(0); // Never to be reached
}

Bullet* WorldObjectBuilder::buildBullet() {

}

Rocket* WorldObjectBuilder::buildRocket() {

}

Ship* WorldObjectBuilder::buildShip() {

}

WorldObject* WorldObjectBuilder::buildWorldObject() {

}
