#include "worldtreescanner.h"

#include <algorithm>
#include <cassert>
#include <unordered_set>

#include "collision/collisiondetector.h"

#include "geometry/sphere.h"

#include "universe/sector.h"
#include "universe/universe.h"

#include "voxel/voxeltreequery.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"


WorldTreeScanner::WorldTreeScanner():
    m_scanInterval(0.0f),
    m_scanCountdown(0.0f),
    m_scanRadius(0.0f)
{
}

WorldTreeScanner::~WorldTreeScanner() = default;

float WorldTreeScanner::scanInterval() const {
    return m_scanInterval;
}

void WorldTreeScanner::setScanInterval(float scanInterval) {
    m_scanInterval = scanInterval;
}

float WorldTreeScanner::scanRadius() const {

    return m_scanRadius;
}

void WorldTreeScanner::setScanRadius(float scanRadius) {
    m_scanRadius = scanRadius;
}

const std::unordered_set<WorldObject*>& WorldTreeScanner::worldObjects() {
    return m_worldObjects;
}

void WorldTreeScanner::update(float deltaSec, WorldObject* worldObject) {
    update(deltaSec, worldObject, worldObject->sector(), worldObject->transform().position());
}

void WorldTreeScanner::update(float deltaSec, Sector* sector, const glm::vec3& position) {
    update(deltaSec, nullptr, sector, position);
}

const std::unordered_set<WorldObject*>& WorldTreeScanner::foundWorldObjects() {
    return m_foundWorldObjects;
}

const std::unordered_set<WorldObject*>& WorldTreeScanner::lostWorldObjects() {
    return m_lostWorldObjects;
}

void WorldTreeScanner::onFoundWorldObject(WorldObject* worldObject) {

}

void WorldTreeScanner::onLostWorldObject(WorldObject* worldObject) {

}

void WorldTreeScanner::update(float deltaSec, WorldObject* worldObject, Sector* sector, const glm::vec3& position) {
    m_foundWorldObjects.clear();
    m_lostWorldObjects.clear();

    m_worldObject = worldObject;
    m_sector = sector;
    m_position = position;

    m_scanCountdown -= deltaSec;
    if(m_scanCountdown < 0) {
        m_scanCountdown = m_scanInterval;
        scan();
    }
}

void WorldTreeScanner::scan() {
    m_foundWorldObjects.clear();
    m_lostWorldObjects = std::move(m_worldObjects);

    m_worldObjects = worldObjectsInRange();

    for (WorldObject* worldObject : m_worldObjects) {
        bool existed = m_lostWorldObjects.erase(worldObject) > 0;

        if (!existed) {
            m_foundWorldObjects.insert(worldObject);
        }
    }

    for(WorldObject* worldObject : m_foundWorldObjects) {
        onFoundWorldObject(worldObject);
    }
    for(WorldObject* worldObject : m_lostWorldObjects) {
        onLostWorldObject(worldObject);
    }
}

std::unordered_set<WorldObject*> WorldTreeScanner::worldObjectsInRange() {
    std::unordered_set<WorldObject*> result;
    Sphere scanSphere(m_position, m_scanRadius);

    std::unordered_set<WorldTreeGeode*> foundGeodes;

    if (m_worldObject) {
        WorldTreeQuery worldTreeQuery(&m_sector->worldTree(), &scanSphere, m_worldObject->collisionDetector().geode()->hint(), &m_worldObject->collisionFilter());
        foundGeodes = worldTreeQuery.nearGeodes();
    } else {
        WorldTreeQuery worldTreeQuery(&m_sector->worldTree(), &scanSphere, WorldTreeHint());
        foundGeodes = worldTreeQuery.nearGeodes();
    }

    for (WorldTreeGeode* foundGeode : foundGeodes) {
        WorldObject* worldObject = foundGeode->worldObject();

        if (VoxelTreeQuery(&worldObject->collisionDetector().voxelTree(), &scanSphere).areVoxelsIntersecting()) {
            result.insert(worldObject);
        }
    }

    return result;
}

