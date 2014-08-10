#include "worldobjectgeometryhelper.h"

#include "worldobject/worldobject.h"
#include "voxel/voxelclusterbounds.h"


float WorldObjectGeometryHelper::sphereToSphereDistance(WorldObject* self, WorldObject* other) {
    return glm::length(self->transform().position() - other->transform().position())
        - self->bounds().minimalGridSphere().radius() * self->transform().scale()
        - other->bounds().minimalGridSphere().radius() * other->transform().scale();
}

WorldObject* WorldObjectGeometryHelper::closestObject(WorldObject& self, std::unordered_set<WorldObject*>* objects) {
    WorldObject* closestObject = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (WorldObject* object : *objects) {
        float distance = glm::length(object->transform().position() - self.transform().position());
        if (distance < closestDistance) {
            closestDistance = distance;
            closestObject = object;
        }
    }
    return closestObject;
}

WorldObject* WorldObjectGeometryHelper::closestObject(WorldObject& self, std::vector<Handle<WorldObject>>* objects) {
    WorldObject* closestObject = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (Handle<WorldObject>& object : *objects) {
        if (object.valid()) {
            float distance = glm::length(object->transform().position() - self.transform().position());
            if (distance < closestDistance) {
                closestDistance = distance;
                closestObject = object.get();
            }
        }
    }
    return closestObject;
}
