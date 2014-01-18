#pragma once

#include "world/world.h"

#include "player.h"
#include "camera.h"


class TargetSelector {
public:
    TargetSelector(Player *player, Camera *camera);

    void setWindowSize(int width, int height);

    void selectNextTarget();
    void selectPreviousTarget();

    glm::vec3 findTargetPoint(double x, double y);


private:
    int m_windowWidth, m_windowHeight, m_cursorMaxDistance;
    World *m_world;
    Camera *m_camera;
    Player *m_player;


    template<typename IteratorType>
    WorldObject* findNextTarget(IteratorType begin, IteratorType end);

    std::function<bool(WorldObject*)> canLockOnPredicate();
};
