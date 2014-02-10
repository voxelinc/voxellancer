#include "hud.h"

#include <algorithm>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "etc/windowmanager.h"

#include "utils/tostring.h"
#include "utils/geometryhelper.h"

#include "world/world.h"

#include "worldtree/worldtreequery.h"

#include "worldobject/ship.h"

#include "hudget.h"
#include "hudobjectdelegate.h"
#include "objecthudget.h"

#include "player.h"




HUD::HUD(Player* player, Viewer* viewer):
    m_player(player),
    m_viewer(viewer),
    m_crossHair(this),
    m_aimHelper(this),
    m_sphere(glm::vec3(0, 0, 0), 5.0f),
    m_scanner(&World::instance()->worldTree())
{
    m_scanner.setScanRadius(1050.0f);
    m_hudgets.push_back(&m_crossHair);
    m_hudgets.push_back(&m_aimHelper);
}

Player* HUD::player() {
    return m_player;
}

glm::vec3 HUD::centerOfView() const {
    return m_player->cameraDolly().cameraHead().position();
}

const Sphere& HUD::sphere() const {
    return m_sphere;
}

CrossHair& HUD::crossHair() {
    return m_crossHair;
}

AimHelperHudget& HUD::aimHelper() {
    return m_aimHelper;
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
    m_objectDelegates[objectDelegate->worldObject()] = objectDelegate;
    addHudget(objectDelegate->hudget());
}

void HUD::removeObjectDelegate(HUDObjectDelegate* objectDelegate) {
    std::function<bool(std::pair<WorldObject*, HUDObjectDelegate*>)> findDelegatePredicate = [&](std::pair<WorldObject*, HUDObjectDelegate*> pair) {
        return pair.second == objectDelegate;
    };
    std::map<WorldObject*, HUDObjectDelegate*>::iterator i = std::find_if(m_objectDelegates.begin(), m_objectDelegates.end(), findDelegatePredicate);

    assert(i != m_objectDelegates.end());
    m_objectDelegates.erase(i);

    removeHudget(objectDelegate->hudget());

    delete objectDelegate;
}

HUDObjectDelegate* HUD::objectDelegate(WorldObject* worldObject) {
    std::map<WorldObject*, HUDObjectDelegate*>::iterator i = m_objectDelegates.find(worldObject);
    return i == m_objectDelegates.end() ? nullptr : i->second;
}

void HUD::setCrossHairOffset(const glm::vec2& mousePosition) {
    CameraHead& cameraHead = m_player->cameraDolly().cameraHead();

    float fovy = m_viewer->view().fovy();
    float nearZ = m_viewer->view().zNear();
    float ar = m_viewer->view().aspectRatio();
    float d = glm::length(glm::vec2(1.0f, nearZ));

    float nearPlaneHeight = 2 * std::tan(fovy / 2.0f);
    float nearPlaneWidth = nearPlaneHeight * ar;

    glm::vec3 nearPlaneTarget = glm::vec3(mousePosition.x * nearPlaneWidth / 2.0f, mousePosition.y * nearPlaneHeight / 2.0f, -nearZ);

    m_crossHair.pointToLocalPoint(nearPlaneTarget);
}

void HUD::update(float deltaSec) {
    updateScanner(deltaSec);

    Ray toCrossHair = Ray::fromTo(m_player->cameraDolly().cameraHead().position(), m_crossHair.worldPosition());

    for (Hudget* hudget : m_hudgets) {
        hudget->pointerAt(toCrossHair, m_crossHair.actionActive());
        hudget->update(deltaSec);
    }
}

void HUD::draw() {
    for (Hudget* hudget : m_hudgets) {
        if (hudget->visible()) {
            hudget->draw();
        }
    }
}

void HUD::onClick(int button) {
    Ray toCrossHair = Ray::fromTo(m_player->cameraDolly().cameraHead().position(), m_crossHair.worldPosition());
    WorldTreeQuery wordltreequery(&World::instance()->worldTree(), &toCrossHair, nullptr, nullptr);
    ObjectHudget* first = nullptr;
    for (Hudget* hudget : m_hudgets) {
        if (hudget->isAt(toCrossHair)) {
            // Aweful, must be changed
            ObjectHudget* oHudget = dynamic_cast<ObjectHudget*>(hudget);
            if (!oHudget) {
                continue;
            }
            if (!first) {
                first = oHudget;
            } else {
                if (glm::length(oHudget->objectDelegate()->worldObject()->transform().position() - m_player->playerShip()->transform().position()) < glm::length(first->objectDelegate()->worldObject()->transform().position() - m_player->playerShip()->transform().position())) {
                    first = oHudget;
                }
            }
        }
    }
    if (first) {
        first->onClick();
    }
}

void HUD::updateScanner(float deltaSec) {
    m_scanner.update(deltaSec, m_player->playerShip());

    for(WorldObject* worldObject : m_scanner.foundWorldObjects()) {
        if(worldObject->objectInfo().showOnHud()) {
            HUDObjectDelegate* objectDelgate = new HUDObjectDelegate(this, worldObject);
            addObjectDelegate(objectDelgate);
        }
    }

    for(WorldObject* worldObject : m_scanner.lostWorldObjects()) {
        HUDObjectDelegate* objectDelgate = objectDelegate(worldObject);
        if(objectDelgate) {
            removeObjectDelegate(objectDelgate);
        }
    }
}

