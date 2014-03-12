#pragma once

#include "bindings.h"

class WorldObjectBindings : public Bindings {
public:
    WorldObjectBindings(GamePlayScript& script);

protected:
    virtual void initialize();

    apikey apiPlayerShip();
    apikey apiCreateShip(const std::string& name);
    int apiSpawn(apikey worldObject);

    int apiSetPosition(apikey worldObject, const glm::vec3& position);
    int apiSetOrientation(apikey worldObject, const glm::vec3& orientation);
    glm::vec3 apiPosition(apikey worldObject);
    glm::vec3 apiOrientation(apikey worldObject);

    apikey apiOnWorldObjectDestroyed(apikey worldObject, const std::string& callback);

};