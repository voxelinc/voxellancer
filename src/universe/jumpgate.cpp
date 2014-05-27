#include "jumpgate.h"

#include <iostream>

#include "collision/collisiondetector.h"

#include "geometry/line.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"

#include "universe/sector.h"

#include "voxel/voxelclusterbounds.h"

#include "worldobject/worldobjectinfo.h"

#include "worldtree/worldtreescanner.h"


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

    m_scanner->setScanRadius(bounds().sphere().radius() * 2.0f);
    m_scanner->update(deltaSec, this);

    for (WorldObject* object : m_scanner->worldObjects()) {
        if (m_lastPositions.find(object) != m_lastPositions.end()) {
            Line line(m_lastPositions[object], object->transform().position());

            if (crossesWarpzone(line)) {
                transfer(object);
            }
        }

        m_lastPositions[object] = object->transform().position();
    }
}

bool Jumpgate::crossesWarpzone(const Line& line) {
    Plane plane (transform().position(), transform().orientation() * glm::vec3(0.0f, 0.0f, -1.0f));

    bool intersects;
    glm::vec3 point(plane.intersectionPoint(line, intersects));

    if (intersects) { std::cout << "Interssda" << std::endl;
        if (glm::length(point - transform().position()) < bounds().sphere().radius() * 0.5f) {
            return true;
        }
    }

    return false;
}

void Jumpgate::transfer(WorldObject* object) {
    std::cout << "Transfering " << object->info().name() << " to " << m_buddy->sector()->name() << std::endl;

    glow::ref_ptr<WorldObject> l (object);

    object->transform().setPosition(m_buddy->transform().position() + glm::vec3(0, 0, -100));
    object->warp(*m_buddy->sector());
}


