#include "jumpgate.h"

#include <iostream>

#include "collision/collisiondetector.h"

#include "geometry/sphere.h"

#include "universe/sector.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobjectinfo.h"

#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"


Jumpgate::Jumpgate() = default;

Jumpgate::~Jumpgate() = default;

Jumpgate* Jumpgate::buddy() {
    return m_buddy.get();
}

void Jumpgate::setBuddy(Jumpgate* buddy) {
    m_buddy = makeHandle(buddy);
}

void Jumpgate::update(float deltaSec) {
    WorldObject::update(deltaSec);

    m_sphere = Sphere(bounds().sphere().position(), bounds().sphere().radius()/2.0f);

    for (WorldObject* object : scan()) {
        transfer(object);
    }
}

std::unordered_set<WorldObject*> Jumpgate::scan() {
    WorldTreeQuery query(&sector()->worldTree(), &m_sphere, collisionDetector().geode()->hint(), &collisionFilter());
    return query.intersectingWorldObjects();
}

void Jumpgate::transfer(WorldObject* object) {
    std::cout << "Transfering " << object->info().name() << " to " << m_buddy->sector()->name() << std::endl;

    glow::ref_ptr<WorldObject> l (object);

    object->transform().setPosition(m_buddy->transform().position() + glm::vec3(0, 0, -100));
    object->warp(*m_buddy->sector());
}


