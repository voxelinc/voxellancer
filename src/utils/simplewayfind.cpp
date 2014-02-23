#include "simplewayfind.h"

#include "world/world.h"
#include "geometry/capsule.h"
#include "worldtree/worldtreequery.h"
#include "worldobject/worldobject.h"
#include "utils/geometryhelper.h"
#include "collision/collisionfilter.h"
#include "voxel/voxelclusterbounds.h"


glm::vec3 SimpleWayfind::calculateTravelPoint(WorldObject& object, glm::vec3 targetPoint) {
    //Wayfinding doesn't care about projectiles
    CollisionFilter filter(object.collisionFilter());
    filter.setCollideableWith(CollisionFilterClass::Bullet, false);
    filter.setCollideableWith(CollisionFilterClass::Rocket, false);

    Capsule capsule = Capsule(object.transform().position(), targetPoint - object.transform().position(), object.bounds().sphere().radius());
    std::unordered_set<WorldObject*> obstacles = WorldTreeQuery(&World::instance()->worldTree(), &capsule, nullptr, &filter).intersectingWorldObjects();

    if (!obstacles.empty()) {
        WorldObject* obstacle = GeometryHelper::closestObject(object, &obstacles);
        if (obstacle) {
            targetPoint = calculateEvasionPointFor(object, *obstacle, targetPoint);
        }
    }

    return targetPoint;
}

glm::vec3 SimpleWayfind::calculateEvasionDirectionFor(WorldObject& self, WorldObject& obstacle, const glm::vec3& targetPoint) {
    // look at the boundingSphere and find out which direction is the shortest way around
    glm::vec3 toTarget = targetPoint - self.transform().position();
    glm::vec3 toObject = obstacle.transform().position() - self.transform().position();

    float dotP = glm::dot(toTarget, toObject);
    float cosAlpha = dotP / (glm::length(toTarget) * glm::length(toObject));

    glm::vec3 crossPoint = self.transform().position() + (glm::normalize(toTarget) * cosAlpha * glm::length(toObject));
    return glm::normalize(crossPoint - obstacle.transform().position());
}

glm::vec3 SimpleWayfind::calculateEvasionPointFor(WorldObject& self, WorldObject& obstacle, const glm::vec3& targetPoint) {
    glm::vec3 evasionDirection = calculateEvasionDirectionFor(self, obstacle, targetPoint);
    // Set the evasion point a bit afar so we aim for a safe distance.
    // We will not actually get that far because the line of sight will most likely be free earlier
    float evasionDistance = (obstacle.bounds().sphere().radius()
        + self.bounds().sphere().radius()) * 2.f;
    return obstacle.transform().position() + evasionDirection * evasionDistance;
}

