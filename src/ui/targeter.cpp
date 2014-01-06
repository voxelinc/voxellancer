#include "ui/targeter.h"

Targeter::Targeter(Player *player, Camera *camera){
    m_player = player;
    m_camera = camera;
    m_world = World::instance();
}

void Targeter::setWindowSize(int width, int height){
    m_windowHeight = height;
    m_windowWidth = width;
    m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth) / 2;
}


void Targeter::selectNextTarget(){
    m_player->playerShip()->setTargetObject(findNextTarget());
}

void Targeter::selectPreviousTarget(){
        m_player->playerShip()->setTargetObject(findPreviousTarget());
}

WorldObject* Targeter::findNextTarget(){
    std::list<WorldObject*>& worldObjects = World::instance()->worldObjects();

    if (!m_player->playerShip()->targetObject()){
        auto iterator = worldObjects.begin();
        // find next lockable target
        while (iterator != worldObjects.end() && (!(*iterator)->objectInfo().canLockOn() || *iterator == m_player->playerShip())){
            ++iterator;
        }
        if (iterator == worldObjects.end())
            return nullptr;
        return *iterator;
    }
    else {
        // Find current target
        for (auto iterator = worldObjects.begin(); iterator != worldObjects.end(); ++iterator){
            if (*iterator == m_player->playerShip()->targetObject()){
                ++iterator;
                // find next lockable target
                while (iterator != worldObjects.end() && (!(*iterator)->objectInfo().canLockOn() || *iterator == m_player->playerShip())){
                    ++iterator;
                }
                if (iterator == worldObjects.end())
                    return nullptr;
                return *iterator;
            }
        }
    }
    return nullptr;
}

WorldObject* Targeter::findPreviousTarget(){
    std::list<WorldObject*>& worldObjects = World::instance()->worldObjects();

    if (!m_player->playerShip()->targetObject()){
        auto iterator = worldObjects.rbegin();
        // find next lockable target
        while (iterator != worldObjects.rend() && (!(*iterator)->objectInfo().canLockOn() || *iterator == m_player->playerShip())){
            ++iterator;
        }
        if (iterator == worldObjects.rend())
            return nullptr;
        return *iterator;
    }
    else {
        // Find current target backwards
        for (auto iterator = worldObjects.rbegin(); iterator != worldObjects.rend(); ++iterator){
            if (*iterator == m_player->playerShip()->targetObject()){
                ++iterator;
                // find next lockable target
                while (iterator != worldObjects.rend() && (!(*iterator)->objectInfo().canLockOn() || *iterator == m_player->playerShip())){
                    ++iterator;
                }
                if (iterator == worldObjects.rend())
                    return nullptr;
                return *iterator;
            }
        }
    }
    return nullptr;
}


glm::vec3 Targeter::findTargetPoint(double x, double y){
    glm::vec4 pointEnd((x * 2 / m_windowWidth - 1), -1 * (y * 2 / m_windowHeight - 1), 1, 1); //get normalized device coords
    pointEnd = glm::inverse(m_camera->viewProjection())*pointEnd; //find point on zfar
    glm::vec3 vec = glm::vec3(pointEnd); // no need for w component
    vec = glm::normalize(vec); // normalize
    vec *= m_player->playerShip()->minAimDistance(); // set aimdistance
    vec += m_camera->position(); //adjust for camera translation
    return vec;
}
