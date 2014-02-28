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

const std::list<WorldObject*>& WorldTreeScanner::worldObjects() {
    return m_worldObjects;
}

void WorldTreeScanner::update(float deltaSec, WorldObject* worldObject) {
    update(deltaSec, worldObject, worldObject->transform().position());
}

void WorldTreeScanner::update(float deltaSec, const glm::vec3& position) {
    update(deltaSec, nullptr, position);
}

const std::list<WorldObject*>& WorldTreeScanner::foundWorldObjects() {
    return m_foundWorldObjects;
}

const std::list<WorldObject*>& WorldTreeScanner::lostWorldObjects() {
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
    Sphere scanSphere(position, m_scanRadius);

    WorldTreeQuery worldTreeQuery(&World::instance()->worldTree(), &scanSphere, worldObject->collisionDetector().geode()->containingNode(), &worldObject->collisionFilter());
    std::unordered_set<WorldTreeGeode*> foundGeodes = worldTreeQuery.nearGeodes();

    // Unordered sets for more performance
    std::unordered_set<WorldObject*> lostWorldObjects(m_worldObjects.begin(), m_worldObjects.end()); // Re-Found objects are removed from this
    std::unordered_set<WorldObject*> worldObjects(m_worldObjects.begin(), m_worldObjects.end()); // Re-Found objects are removed from this

    for(WorldTreeGeode* foundGeode : foundGeodes) {
        WorldObject* foundWorldObject = foundGeode->worldObject();

        if(!VoxelTreeQuery(&foundWorldObject->collisionDetector().voxelTree(), &scanSphere).areVoxelsIntersecting()) {
            continue;
        }

        std::unordered_set<WorldObject*>::iterator j = worldObjects.find(foundWorldObject);

        if(j == worldObjects.end()) { // Object not yet found, add to newly found
            m_foundWorldObjects.push_back(foundWorldObject);
        } else { // object found again, thus wasn't lost
            lostWorldObjects.erase(foundWorldObject);
        }
    }

    m_lostWorldObjects = std::list<WorldObject*>(lostWorldObjects.begin(), lostWorldObjects.end());

    for(WorldObject* worldObject : m_foundWorldObjects) {
        m_worldObjects.push_back(worldObject);
        onFoundWorldObject(worldObject);
    }

    for(WorldObject* worldObject : m_lostWorldObjects) {
        m_worldObjects.remove(worldObject);
        onLostWorldObject(worldObject);
    }
}
