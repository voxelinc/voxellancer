#include "simplewayfind.h"

#include "world/world.h"
#include "geometry/capsule.h"
#include "worldtree/worldtreequery.h"
#include "worldobject/worldobject.h"


glm::vec3 SimpleWayfind::calculateTravelPoint(WorldObject& object, const glm::vec3& targetPoint) {
    Capsule capsule = Capsule(object.transform().position(), targetPoint - object.transform().position(), object.minimalGridSphere().radius());
    std::set<WorldObject*> obstacles = WorldTreeQuery(&World::instance()->worldTree(), &capsule).intersectingWorldObjects();

    if (obstacles.size() > 1) { // we will always be in it
        WorldObject* obstacle = closestObjectExceptSelf(object, &obstacles);
        if (obstacle) {
            return calculateEvasionPointFor(object, *obstacle, targetPoint);
        } else {
            return targetPoint;
        }
    } else {
        return targetPoint;
    }
}

glm::vec3 SimpleWayfind::calculateEvasionPointFor(WorldObject& self, WorldObject& obstacle, const glm::vec3& targetPoint) {
    // look at the boundingSphere and find out which direction is the shortest way around
    glm::vec3 toTarget = targetPoint - self.transform().position();
    glm::vec3 toObject = obstacle.transform().position() - self.transform().position();
    float dotP = glm::dot(toTarget, toObject);
    float cosAlpha = dotP / (glm::length(toTarget) * glm::length(toObject));
    glm::vec3 crossPoint = self.transform().position() + (glm::normalize(toTarget) * cosAlpha * glm::length(toObject));
    glm::vec3 evasionDirection = glm::normalize(crossPoint - obstacle.transform().position());

    // Set the evasion point a bit afar so we aim for a safe distance.
    // We will not actually get that far because the line of sight will most likely be free earlier
    float evasionDistance = (obstacle.minimalGridSphere().radius() + self.minimalGridSphere().radius()) * 2.f;
    return obstacle.transform().position() + evasionDirection * evasionDistance;
}

WorldObject* SimpleWayfind::closestObjectExceptSelf(WorldObject& self, std::set<WorldObject*>* objects){
    WorldObject* closestObject = nullptr;
    float closestDistance = -1;

    for (WorldObject* object : *objects) {
        float distance = glm::length(object->transform().position() - self.transform().position());
        if ((closestDistance == -1 || distance < closestDistance) && object != &self){
            closestDistance = distance;
            closestObject = object;
        }
    }
    return closestObject;
}