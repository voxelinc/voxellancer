#include "hud.h"

#include <algorithm>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "etc/windowmanager.h"

#include "utils/tostring.h"
#include "utils/math.h"

#include "player.h"

#include "hudget.h"
#include "hudobjectdelegate.h"


HUD::HUD(Player* player, Viewer* viewer):
    m_player(player),
    m_viewer(viewer),
    m_crossHair(this),
    m_sphere(glm::vec3(0, 0, 0), 5.0f),
    m_scanner(&World::instance()->worldTree())
{
    m_scanner.setScanRadius(150.0f);
    m_hudgets.push_back(&m_crossHair);
}

void HUD::setCrossHairOffset(const glm::vec2& mousePosition) {
    CameraHead& cameraHead = m_player->cameraDolly().cameraHead();

    float fovy = m_viewer->view().fovy();
    float nearZ = m_viewer->view().zNear();
    float ar = m_viewer->view().aspectRatio();
    float d = glm::length(glm::vec2(1.0f, nearZ));

    float nearPlaneHeight = 2 * std::tan(glm::radians(fovy) / 2.0f);
    float nearPlaneWidth = nearPlaneHeight * ar;

    glm::vec3 nearPlaneTarget = glm::vec3(mousePosition.x * nearPlaneWidth / 2.0f, mousePosition.y * nearPlaneHeight / 2.0f, -nearZ);

    glm::quat offset = Math::differenceFromViewDirection(nearPlaneTarget);

    m_crossHair.setOrientationOffset(offset);
}

Player* HUD::player() {
    return m_player;
}

const Sphere& HUD::sphere() const {
    return m_sphere;
}

CrossHair& HUD::crossHair() {
    return m_crossHair;
}

glm::vec3 HUD::position() const {
    return m_player->cameraDolly().cameraHead().position() + m_player->cameraDolly().cameraHead().orientation() * m_sphere.position();
}

glm::quat HUD::orientation() const {
    return m_player->cameraDolly().cameraHead().orientation();
}

void HUD::addHudget(Hudget* hudget) {
    m_hudgets.push_back(hudget);
}

void HUD::removeHudget(Hudget* hudget) {
    m_hudgets.remove(hudget);
}

void HUD::addObjectDelegate(HUDObjectDelegate* objectDelegate) {
    m_objectDelegates.push_back(objectDelegate);
    addHudget(objectDelegate->hudget());
}

void HUD::removeObjectDelegate(HUDObjectDelegate* objectDelegate) {
    m_objectDelegates.remove(objectDelegate);
    removeHudget(objectDelegate->hudget());

    delete objectDelegate;
}

const std::list<HUDObjectDelegate*>& HUD::objectDelegates() const {
    return m_objectDelegates;
}

HUDObjectDelegate* HUD::objectDelegate(WorldObject* worldObject) {
    std::list<HUDObjectDelegate*>::iterator i = std::find_if(m_objectDelegates.begin(), m_objectDelegates.end(), [&](HUDObjectDelegate* objectDelegate) {
        return objectDelegate->worldObject() == worldObject;
    });
    return i == m_objectDelegates.end() ? nullptr : *i;
}

void HUD::update(float deltaSec) {
    m_scanner.update(deltaSec, m_player->playerShip());

    for(WorldObject* worldObject : m_scanner.foundWorldObjects()) {
        HUDObjectDelegate* objectDelgate = new HUDObjectDelegate(this, worldObject);
        addObjectDelegate(objectDelgate);
    }

    for(WorldObject* worldObject : m_scanner.lostWorldObjects()) {
        HUDObjectDelegate* objectDelgate = objectDelegate(worldObject);
        removeObjectDelegate(objectDelgate);
    }

    for(Hudget* hudget : m_hudgets) {
        hudget->update(deltaSec);
    }
}

void HUD::draw() {
    for(Hudget* hudget : m_hudgets) {
        hudget->draw();
    }
}



