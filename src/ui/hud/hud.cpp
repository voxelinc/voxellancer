#include "hud.h"

#include <algorithm>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glow/Program.hpp>


#include "etc/windowmanager.h"

#include "utils/tostring.h"
#include "utils/geometryhelper.h"

#include "world/world.h"

#include "worldobject/ship.h"

#include "hudget.h"
#include "hudobjectdelegate.h"

#include "player.h"
#include "voxel/voxelrenderer.h"
#include "geometry/ray.h"
#include "display/viewer.h"
#include "crosshair.h"
#include "worldtree/worldtreescanner.h"
#include "aimhelperhudget.h"
#include "ui/objectinfo.h"
#include "display/view.h"


HUD::HUD(Player* player, Viewer* viewer):
    m_player(player),
    m_viewer(viewer),
    m_sphere(glm::vec3(0, 0, 0), 5.0f),
    m_crossHair(new CrossHair(this)),
    m_aimHelper(new AimHelperHudget(this)),
    m_scanner(new WorldTreeScanner(&World::instance()->worldTree()))
{
    m_scanner->setScanRadius(1050.0f);
    m_hudgets.push_back(m_crossHair.get());
    m_hudgets.push_back(m_aimHelper.get());
}

HUD::~HUD() = default;

Player* HUD::player() {
    return m_player;
}

glm::vec3 HUD::centerOfView() const {
    return m_player->cameraPosition();
}

const Sphere& HUD::sphere() const {
    return m_sphere;
}

CrossHair& HUD::crossHair() {
    return *m_crossHair;
}

AimHelperHudget& HUD::aimHelper() {
    return *m_aimHelper;
}

glm::vec3 HUD::position() const {
    return m_player->cameraPosition() + m_player->cameraOrientation() * m_sphere.position();
}

glm::quat HUD::orientation() const {
    return m_player->cameraOrientation();
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
    float fovy = m_viewer->view().fovy();
    float nearZ = m_viewer->view().zNear();
    float ar = m_viewer->view().aspectRatio();
    float d = glm::length(glm::vec2(1.0f, nearZ));

    float nearPlaneHeight = 2 * std::tan(fovy / 2.0f);
    float nearPlaneWidth = nearPlaneHeight * ar;

    glm::vec3 nearPlaneTarget = glm::vec3(mousePosition.x * nearPlaneWidth / 2.0f, mousePosition.y * nearPlaneHeight / 2.0f, -nearZ);
    m_crossHair->pointToLocalPoint(nearPlaneTarget);
}

void HUD::update(float deltaSec) {
    updateScanner(deltaSec);

    Ray toCrossHair = Ray::fromTo(m_player->cameraPosition(), m_crossHair->worldPosition());

    for (Hudget* hudget : m_hudgets) {
        hudget->pointerAt(toCrossHair, m_crossHair->actionActive());
        hudget->update(deltaSec);
    }
}

void HUD::draw() {
    glow::Uniform<glm::vec3>* lightuniform = VoxelRenderer::instance()->program()->getUniform<glm::vec3>("lightdir");
    glm::vec3 oldLightdir = lightuniform->value();
    lightuniform->set(m_player->cameraOrientation() * glm::vec3(0,0,1));

    for (Hudget* hudget : m_hudgets) {
        if (hudget->visible()) {
            hudget->draw();
        }
    }

    lightuniform->set(oldLightdir);
}

void HUD::updateScanner(float deltaSec) {
    if (m_player->playerShip()) {
        m_scanner->update(deltaSec, m_player->playerShip());

        for (WorldObject* worldObject : m_scanner->foundWorldObjects()) {
            if (worldObject->objectInfo().showOnHud()) {
                HUDObjectDelegate* objectDelgate = new HUDObjectDelegate(this, worldObject);
                addObjectDelegate(objectDelgate);
            }
        }

        for (WorldObject* worldObject : m_scanner->lostWorldObjects()) {
            HUDObjectDelegate* objectDelgate = objectDelegate(worldObject);
            if (objectDelgate) {
                removeObjectDelegate(objectDelgate);
            }
        }
    } else { // no player ship, clear all delegates
        for (WorldObject* worldObject : m_scanner->worldObjects()) {
            HUDObjectDelegate* objectDelgate = objectDelegate(worldObject);
            if (objectDelgate) {
                removeObjectDelegate(objectDelgate);
            }
        }
    }
}

