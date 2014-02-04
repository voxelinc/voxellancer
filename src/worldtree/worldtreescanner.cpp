#include "worldtreescanner.h"

#include <algorithm>
#include <cassert>
#include <set>

#include "geometry/sphere.h"

#include "voxel/voxeltreequery.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"
#include "collision/collisiondetector.h"



WorldTreeScanner::WorldTreeScanner(WorldTree* worldTree):
    m_worldTree(worldTree),
    m_scanInterval(0.0f),
    m_scanCountdown(0.0f),
    m_scanRadius(0.0f)
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

std::list<WorldObject*> WorldTreeScanner::worldObjects() {
    return m_worldObjects;
}

void WorldTreeScanner::update(float deltaSec, WorldObject* worldObject) {
    update(deltaSec, worldObject, worldObject->transform().position());
}

void WorldTreeScanner::update(float deltaSec, const glm::vec3& position) {
    update(deltaSec, nullptr, position);
}

std::list<WorldObject*> WorldTreeScanner::foundWorldObjects() {
    return m_foundWorldObjects;
}

std::list<WorldObject*> WorldTreeScanner::lostWorldObjects() {
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

    std::set<WorldTreeGeode*> foundGeodes = WorldTreeQuery(m_worldTree, &scanSphere, worldObject->collisionDetector().geode()->containingNode(), &worldObject->collisionFilter()).nearGeodes();

    m_lostWorldObjects = m_worldObjects; // Re-Found objects are removed from this list

    for(std::set<WorldTreeGeode*>::iterator i = foundGeodes.begin(); i != foundGeodes.end(); ++i) {
        WorldTreeGeode* foundGeode = *i;
        WorldObject* foundWorldObject = foundGeode->worldObject();
        
        if(!VoxelTreeQuery(&foundWorldObject->collisionDetector().voxelTree(), &scanSphere).areVoxelsIntersecting()) {
            continue;
        }

        std::list<WorldObject*>::iterator j = std::find(m_worldObjects.begin(), m_worldObjects.end(), foundWorldObject);

        if(j == m_worldObjects.end()) { // Object not yet found, add to newly found
            m_foundWorldObjects.push_back(foundWorldObject);
        } else { // object found again, thus wasn't lost
            m_lostWorldObjects.remove(foundWorldObject);
        }
    }

    for(WorldObject* worldObject : m_foundWorldObjects) {
        m_worldObjects.push_back(worldObject);
        onFoundWorldObject(worldObject);
    }

    for(WorldObject* worldObject : m_lostWorldObjects) {
        m_worldObjects.remove(worldObject);
        onLostWorldObject(worldObject);
    }
}
