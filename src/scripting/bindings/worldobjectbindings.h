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

    int apiSetPosition(apikey worldObject, float x, float y, float z);
    int apiSetOrientation(apikey worldObject, float x, float y, float z);
    glm::vec3 apiPosition(apikey worldObject);
    glm::vec3 apiOrientation(apikey worldObject);
};