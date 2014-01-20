#include "ui/targetselector.h"

#include <algorithm>


TargetSelector::TargetSelector(Player *player, Camera *camera) {
    m_player = player;
    m_camera = camera;
    m_world = World::instance();
}

void TargetSelector::setWindowSize(int width, int height) {
    m_windowHeight = height;
    m_windowWidth = width;
    m_cursorMaxDistance = glm::min(m_windowHeight, m_windowWidth) / 2;
}

void TargetSelector::selectNextTarget() {
    std::list<WorldObject*>& worldObjects = World::instance()->worldObjects();
    m_player->ship()->setTargetObject(findNextTarget(worldObjects.begin(), worldObjects.end()));
}

void TargetSelector::selectPreviousTarget() {
    std::list<WorldObject*>& worldObjects = World::instance()->worldObjects();
    m_player->ship()->setTargetObject(findNextTarget(worldObjects.rbegin(), worldObjects.rend()));
}

template<typename IteratorType>
WorldObject* TargetSelector::findNextTarget(IteratorType begin, IteratorType end) {
    IteratorType searchBegin = begin;

    if (m_player->ship()->targetObject() != nullptr) {
        searchBegin = std::find(begin, end, m_player->ship()->targetObject());
        searchBegin++;
    }

    IteratorType newTarget = std::find_if(searchBegin, end, canLockOnPredicate());

    if(newTarget == end) {
        newTarget = std::find_if(begin, searchBegin, canLockOnPredicate());
    }

    return newTarget != end ? *newTarget : nullptr;
}

glm::vec3 TargetSelector::findTargetPoint(double x, double y) {
    glm::vec4 pointEnd((x * 2 / m_windowWidth - 1), -1 * (y * 2 / m_windowHeight - 1), 1, 1); //get normalized device coords
    pointEnd = glm::inverse(m_camera->viewProjection())*pointEnd; //find point on zfar
    glm::vec3 vec = glm::vec3(pointEnd); // no need for w component
    vec = glm::normalize(vec); // normalize
    vec *= m_player->ship()->minAimDistance(); // set aimdistance
    vec += m_camera->position(); //adjust for camera translation
    return vec;
}

std::function<bool(WorldObject*)> TargetSelector::canLockOnPredicate() {
    return [] (WorldObject* worldObject) {
        return worldObject->objectInfo().canLockOn();
    };
}

