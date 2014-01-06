#pragma once

#include <GL/glew.h>

//#include <GLFW/glfw3.h>

#include "player.h"
#include "camera.h"
#include "world/world.h"


class Targeter {
public:
    Targeter(Player *player, Camera *camera);
    void setWindowSize(int width, int height);
    void selectNextTarget();
    void selectPreviousTarget();
    glm::vec3 findTargetPoint(double x, double y);
private:
    int m_windowWidth, m_windowHeight, m_cursorMaxDistance;
    World *m_world;
    Camera *m_camera;
    Player *m_player;
    WorldObject* findNextTarget();
    WorldObject* findPreviousTarget();
};