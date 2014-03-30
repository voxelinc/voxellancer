#pragma once

#include "bindings.h"


class WorldObjectBindings : public Bindings {
public:
    WorldObjectBindings(GamePlayScript& script);


protected:
    virtual void bind() override;

    apikey apiPlayerShip();
    apikey apiCreateShip(const std::string& name);
    apikey apiCreateWorldObject(const std::string& name);
    int apiSpawn(apikey worldObject);
    int apiRemove(apikey worldObject);

    int apiSetPosition(apikey worldObject, const glm::vec3& position);
    int apiSetOrientation(apikey worldObject, const glm::vec3& orientation);
    glm::vec3 apiPosition(apikey worldObject);
    glm::vec3 apiOrientation(apikey worldObject);
    int apiSetShowOnHud(apikey worldObject, bool show);
    int apiSetCanLockOn(apikey worldObject, bool lockon);

    apikey apiOnWorldObjectDestroyed(apikey worldObject, const std::string& callback);
    apikey apiOnAABBEntered(apikey worldObject, const glm::vec3& llf, const glm::vec3& urb, const std::string& callback);
};

