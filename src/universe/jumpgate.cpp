#include "jumpgate.h"

#include <iostream>

#include "collision/collisiondetector.h"

#include "geometry/disk.h"
#include "geometry/line.h"
#include "geometry/sphere.h"

#include "physics/physics.h"

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

    physics().setSpeed(Speed(physics().speed().directional(),
                             transform().orientation() * glm::vec3(0.0f, 0.0f, -1.0f) * glm::radians(10.0f)));

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
    Disk disk(transform().position(), transform().orientation() * glm::vec3(0.0f, 0.0f, -1.0f), transform().scale() * 4.0f);
    return disk.intersectionWith(line);
}

void Jumpgate::transfer(WorldObject* object) {
    // think of this as the hyperspace. somebody has to hold the object while it switches sectors otherwise its refCount will frop to 0
    glow::ref_ptr<WorldObject> objectHolder(object);

    object->transform().setPosition(m_buddy->transform().position() + glm::vec3(0, 0, -1.0f));
    object->transform().setOrientation(m_buddy->transform().orientation());

    object->physics().setSpeed(Speed(m_buddy->transform().orientation() * glm::vec3(0, 0, -13), glm::vec3()));

    object->warp(*m_buddy->sector());
}


