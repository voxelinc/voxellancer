#pragma once

#include "bindings.h"

class WorldObjectBindings : public Bindings {
public:
    WorldObjectBindings(GamePlayScript& script);

protected:
    virtual void initialize();

    int apiPlayerShip();
    int apiCreateShip(const std::string& name);
    int apiSpawn(int key);

    int apiSetPosition(int key, float x, float y, float z);
    int apiSetOrientation(int key, float x, float y, float z);
    glm::vec3 apiPosition(int key);
    glm::vec3 apiOrientation(int key);
};