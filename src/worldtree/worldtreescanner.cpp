#include "worldtreescanner.h"

#include <algorithm>
#include <cassert>
#include <unordered_set>

#include "geometry/sphere.h"

#include "voxel/voxeltreequery.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"



WorldTreeScanner::WorldTreeScanner():
    m_scanInterval(0.0f),
    m_scanCountdown(0.0f),
    m_scanRadius(0.0f),
    m_worldObjects(),
    m_foundWorldObjects(),
    m_lostWorldObjects()
{

}

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

const std::set<WorldObject*>& WorldTreeScanner::worldObjects() {
    return m_worldObjects;
}

void WorldTreeScanner::update(float deltaSec, WorldObject* worldObject) {
    update(deltaSec, worldObject, worldObject->transform().position());
}

void WorldTreeScanner::update(float deltaSec, const glm::vec3& position) {
    update(deltaSec, nullptr, position);
}

const std::set<WorldObject*>& WorldTreeScanner::foundWorldObjects() {
    return m_foundWorldObjects;
}

const std::set<WorldObject*>& WorldTreeScanner::lostWorldObjects() {
    return m_lostWorldObjects;
}

void WorldTreeScanner::onFoundWorldObject(WorldObject* worldObject) {

}

void WorldTreeScanner::onLostWorldObject(WorldObject* worldObject) {

}

void WorldTreeScanner::update(float deltaSec, WorldObject* worldObject, const glm::vec3& position) {
    m_foundWorldObjects.clear();
    m_lostWorldObjects.clear();

    m_scanCountdown -= deltaSec;
    if(m_scanCountdown < 0) {
        m_scanCountdown = m_scanInterval;
        scan(worldObject, position);
    }
}

void WorldTreeScanner::scan(WorldObject* worldObject, const glm::vec3& position) {
    std::set<WorldObject*> worldObjects(worldObjectsInRange(worldObject, position));

    m_foundWorldObjects.clear();
    m_lostWorldObjects.clear();

    std::set<WorldObject*>::iterator iLeft = m_worldObjects.begin();
    std::set<WorldObject*>::iterator iRight = worldObjects.begin();

    while (iLeft != m_worldObjects.end() && iRight != worldObjects.end()) {
        WorldObject* left = *iLeft;
        WorldObject* right = *iRight;

        if (left == right) {
            iLeft++;
            iRight++;
        } else if (left < right) {
            m_lostWorldObjects.insert(left);
            iLeft++;
        } else if (right < left) {
            m_foundWorldObjects.insert(right);
            iRight++;
        }
    }

    for (; iLeft != m_worldObjects.end(); iLeft++) {
        m_lostWorldObjects.insert(*iLeft);
    }
    for (; iRight != worldObjects.end(); iRight++) {
        m_foundWorldObjects.insert(*iRight);
    }

    m_worldObjects = worldObjects;

    for(WorldObject* worldObject : m_foundWorldObjects) {
        onFoundWorldObject(worldObject);
    }

    for(WorldObject* worldObject : m_lostWorldObjects) {
        onLostWorldObject(worldObject);
    }
}

std::set<WorldObject*> WorldTreeScanner::worldObjectsInRange(WorldObject* worldObject, const glm::vec3& position) {
    std::set<WorldObject*> result;
    Sphere scanSphere(position, m_scanRadius);

    WorldTreeQuery worldTreeQuery(&World::instance()->worldTree(), &scanSphere, worldObject->collisionDetector().geode()->containingNode(), &worldObject->collisionFilter());
    std::unordered_set<WorldTreeGeode*> foundGeodes = worldTreeQuery.nearGeodes();

    for (WorldTreeGeode* foundGeode : foundGeodes) {
        WorldObject* worldObject = foundGeode->worldObject();

        if (VoxelTreeQuery(&worldObject->collisionDetector().voxelTree(), &scanSphere).areVoxelsIntersecting()) {
            result.insert(worldObject);
        }
    }

    return result;
}

