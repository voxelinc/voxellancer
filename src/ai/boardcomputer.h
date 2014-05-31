#pragma once

#include <vector>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "equipment/enginestate.h"

#include "utils/handle/handle.h"

#include "orderpriority.h"

class WorldObject;

/**
 *  The BoardComputer abstracts the Ship's systems to a level usable to AiTask, Character and Player
 */
class BoardComputer {
public:
    BoardComputer(WorldObject* worldObject);

    WorldObject* worldObject();

    const EngineState& engineState() const;

    void moveTo(const glm::vec3& position, bool decelerate = true, OrderPriority priority = OrderPriority::DEFAULT);
    void rotateTo(const glm::vec3& position, const glm::vec3& up = glm::vec3(0, 0, 0), OrderPriority priority = OrderPriority::DEFAULT);

    void shootBullet(const std::vector<Handle<WorldObject>>& targets, OrderPriority priority = OrderPriority::DEFAULT);
    void shootRockets(WorldObject* target, OrderPriority priority = OrderPriority::DEFAULT);

    virtual void update(float deltaSec);

    void setMoveOrderPriority(OrderPriority priority);
    void setFireOrderPriority(OrderPriority priority);
    void setGeneralOrderPriority(OrderPriority priority);

protected:
    WorldObject* m_worldObject;
    EngineState m_engineState;
    bool m_overwriteEngineState;

    /* Return the euler angles needed to adjust 'up' */
    glm::vec3 rotateUpTo(const glm::vec3& up);
    glm::vec3 rotateUpAuto(const glm::quat& rotation);
    OrderPriority m_moveOrderPriority;
    OrderPriority m_fireOrderPriority;

    bool isMoveOrderAllowed(OrderPriority priority);
    bool isFireOrderAllowed(OrderPriority priority);

    };


