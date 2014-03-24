#include "hud.h"

#include <algorithm>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glow/Program.hpp>

#include "utils/tostring.h"
#include "utils/geometryhelper.h"

#include "world/world.h"
#include <string>

#include "worldtree/worldtreequery.h"

#include "worldobject/ship.h"

#include "hudget.h"
#include "hudobjectdelegate.h"
#include "objecthudget.h"

#include "collision/collisionfilter.h"

#include "player.h"
#include "voxel/voxelrenderer.h"
#include "geometry/ray.h"
#include "display/viewer.h"
#include "crosshair.h"
#include "worldtree/worldtreescanner.h"
#include "aimhelperhudget.h"
#include "ui/objectinfo.h"
#include "display/view.h"
#include "camera/camerahead.h"
#include "textfieldhudget.h"
#include "physics/physics.h"



HUD::HUD(Player* player):
    m_player(player),
    m_viewer(nullptr),
    m_sphere(glm::vec3(0, 0, 0), 5.0f),
    m_crossHair(new CrossHair(this)),
    m_aimHelper(new AimHelperHudget(this)),
    m_scanner(new WorldTreeScanner()),
    m_targetName(new TextFieldHudget(this, glm::normalize(glm::vec3(0, -1.1f, -2)), 0.025f, "")),
    m_speedLabel(new TextFieldHudget(this, glm::normalize(glm::vec3(1.5f, -1.1f, -2)), 0.020f, "")),
    m_target(nullptr),
    m_drawHud("vfx.drawhud")
{
    m_scanner->setScanRadius(1050.0f);
    m_hudgets.push_back(m_crossHair.get());
    m_hudgets.push_back(m_aimHelper.get());
    m_hudgets.push_back(m_targetName.get());
    m_hudgets.push_back(m_speedLabel.get());
}

HUD::~HUD() = default;

Player* HUD::player() {
    return m_player;
}

glm::vec3 HUD::centerOfView() const {
    return m_player->cameraHead().position();
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
    return m_player->cameraHead().position() + m_player->cameraHead().orientation() * m_sphere.position();
}

glm::quat HUD::orientation() const {
    return m_player->cameraHead().orientation();
}

void HUD::addHudget(Hudget* hudget) {
    m_hudgets.push_back(hudget);
}

void HUD::removeHudget(Hudget* hudget) {
    m_hudgets.remove(hudget);
}

void HUD::addObjectDelegate(HUDObjectDelegate* objectDelegate) {
    m_objectDelegates[objectDelegate->worldObject()] = objectDelegate;
    addHudget(&objectDelegate->hudget());
}

void HUD::removeObjectDelegate(HUDObjectDelegate* objectDelegate) {
    std::function<bool(std::pair<WorldObject*, HUDObjectDelegate*>)> findDelegatePredicate = [&](std::pair<WorldObject*, HUDObjectDelegate*> pair) {
        return pair.second == objectDelegate;
    };
    std::map<WorldObject*, HUDObjectDelegate*>::iterator i = std::find_if(m_objectDelegates.begin(), m_objectDelegates.end(), findDelegatePredicate);

    assert(i != m_objectDelegates.end());
    m_objectDelegates.erase(i);

    removeHudget(&objectDelegate->hudget());

    delete objectDelegate;
}

HUDObjectDelegate* HUD::objectDelegate(WorldObject* worldObject) {
    std::map<WorldObject*, HUDObjectDelegate*>::iterator i = m_objectDelegates.find(worldObject);
    return i == m_objectDelegates.end() ? nullptr : i->second;
}

void HUD::setCrossHairOffset(const glm::vec2& mousePosition) {
    assert(m_viewer);
    float fovy = m_viewer->view().fovy();
    float nearZ = m_viewer->view().zNear();
    float ar = m_viewer->view().aspectRatio();

    float nearPlaneHeight = 2 * std::tan(fovy / 2.0f);
    float nearPlaneWidth = nearPlaneHeight * ar;

    glm::vec3 nearPlaneTarget = glm::vec3(mousePosition.x * nearPlaneWidth / 2.0f, mousePosition.y * nearPlaneHeight / 2.0f, -nearZ);
    m_crossHair->pointToLocalPoint(nearPlaneTarget);
}

void HUD::update(float deltaSec) {
    updateFov();
    updateScanner(deltaSec);

    Ray toCrossHair = Ray::fromTo(m_player->cameraHead().position(), m_crossHair->worldPosition());

    if (m_target.get()) {
        m_targetName->setContent(m_target->objectInfo().name());
    } else {
        m_targetName->setContent("no target");
    }

    if (m_player->ship()) {
        m_speedLabel->setContent(std::to_string((int)(glm::length(m_player->ship()->physics().speed().directional()))));
    } else {
        m_speedLabel->setContent("-");
    }

    for (Hudget* hudget : m_hudgets) {
        hudget->pointerAt(toCrossHair, m_crossHair->actionActive());
        hudget->update(deltaSec);
    }
}

void HUD::draw() {
    if (!m_drawHud) {
        return;
    }
    glow::Uniform<glm::vec3>* lightuniform = VoxelRenderer::instance()->program()->getUniform<glm::vec3>("lightdir");
    glm::vec3 oldLightdir = lightuniform->value();
    lightuniform->set(m_player->cameraHead().orientation() * glm::vec3(0,0,1));

    for (Hudget* hudget : m_hudgets) {
        if (hudget->visible()) {
            hudget->draw();
        }
    }

    lightuniform->set(oldLightdir);
}

void HUD::onClick(ClickType clickType) {
    Ray toCrossHair = Ray::fromTo(m_player->cameraHead().position(), m_crossHair.get()->worldPosition());
    for (Hudget* hudget : m_hudgets) {
        if (hudget->isAt(toCrossHair) && hudget != m_crossHair.get()) {
            hudget->onClick(clickType);
            return;
        }
    }
}

void HUD::updateScanner(float deltaSec) {
    if (m_player->ship()) {
        m_scanner->update(deltaSec, m_player->ship());

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

glm::vec3 HUD::applyTo(const glm::vec3 &vertex) const {
    return position() + (orientation() * vertex);
}

void HUD::setTarget(WorldObject* target) {
    m_target = target->handle();
}

WorldObject* HUD::target() {
    return m_target.get();
}

Viewer* HUD::viewer() const {
    return m_viewer;
}

void HUD::updateFov() {
    assert(m_viewer);
    m_fovy = m_viewer->view().fovy() / 2;
    m_fovx = glm::atan(glm::tan(m_fovy)*m_viewer->view().aspectRatio());
}

float HUD::fovy() const {
    return m_fovy;
}

float HUD::fovx() const {
    return m_fovx;
}

void HUD::setViewer(Viewer& viewer) {
    m_viewer = &viewer;
}
