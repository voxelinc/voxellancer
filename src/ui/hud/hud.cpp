#include "hud.h"

#include <algorithm>
#include <cmath>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glow/Program.hpp>

#include "camera/camerahead.h"

#include "collision/collisionfilter.h"

#include "display/view.h"

#include "gamestate/game.h"

#include "geometry/ray.h"

#include "physics/physics.h"

#include "worldobject/worldobjectinfo.h"

#include "utils/tostring.h"
#include "utils/geometryhelper.h"

#include "voxel/voxelrenderer.h"

#include "world/world.h"

#include "worldtree/worldtreescanner.h"
#include "worldtree/worldtreequery.h"

#include "worldobject/ship.h"
#include "worldobject/worldobjectcomponents.h"

#include "hudelements.h"
#include "hudget.h"
#include "hudobjectdelegate.h"
#include "hudgetanimation.h"
#include "hudgethideanimation.h"
#include "objecthudget.h"
#include "player.h"
#include "crosshair.h"
#include "aimhelperhudget.h"
#include "textfieldhudget.h"



HUD::HUD(Player* player):
    m_player(player),
    m_sphere(glm::vec3(0, 0, 0), 5.0f),
    m_crossHair(new CrossHair(this)),
    m_aimHelper(new AimHelperHudget(this)),
    m_scanner(new WorldTreeScanner()),
    m_elements(new HUDElements(*this)),
    m_drawHud("vfx.drawhud"),
    m_view(nullptr)
{
    m_scanner->setScanRadius(500.0f);

    m_elements->addHudget(m_aimHelper);
    m_elements->addHudget(m_crossHair);
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
    m_elements->addHudget(hudget);
}

void HUD::removeHudget(Hudget* hudget) {
    m_elements->removeHudget(hudget);
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
    assert(m_view);
    float fovy = m_view->fovy();
    float nearZ = m_view->zNear();
    float ar = m_view->aspectRatio();

    float nearPlaneHeight = 2 * std::tan(fovy / 2.0f);
    float nearPlaneWidth = nearPlaneHeight * ar;

    glm::vec3 nearPlaneTarget = glm::vec3(mousePosition.x * nearPlaneWidth / 2.0f, mousePosition.y * nearPlaneHeight / 2.0f, -nearZ);
    m_crossHair->pointToLocalPoint(nearPlaneTarget);
}

void HUD::update(float deltaSec) {
    updateFov();
    updateScanner(deltaSec);

    if (m_target.get()) {
        m_elements->setTargetName(m_target->info().name());
    } else {
        m_elements->setTargetName("no target");
    }

    if (m_player->ship()) {
        m_elements->setSpeed(std::to_string((int)(glm::length(m_player->ship()->physics().speed().directional()))));
        m_elements->setShieldStatus(m_player->ship()->info().shieldStatus());
    } else {
        m_elements->setSpeed("-");
        m_elements->setShieldStatus("-");
    }

    Ray toCrossHair = Ray::fromTo(m_player->cameraHead().position(), m_crossHair->worldPosition());
    for (std::unique_ptr<Hudget>& hudget : m_elements->hudgets()) {
        hudget->pointerAt(toCrossHair, m_crossHair->actionActive());
    }

    m_elements->update(deltaSec);
}

void HUD::draw() {
    if (!m_drawHud) {
        return;
    }

    glow::Uniform<glm::vec3>* lightuniform = VoxelRenderer::instance()->program()->getUniform<glm::vec3>("lightdir");
    glm::vec3 oldLightdir = lightuniform->value();
    lightuniform->set(m_player->cameraHead().orientation() * glm::vec3(0,0,1));

    m_elements->draw();

    lightuniform->set(oldLightdir);
}

void HUD::onClick(ClickType clickType) {
    Ray toCrossHair = Ray::fromTo(m_player->cameraHead().position(), m_crossHair->worldPosition());
    ObjectHudget* smallestTargetHudget = nullptr;
    Hudget* otherHudget = nullptr;

    for (std::unique_ptr<Hudget>& hudget : m_elements->hudgets()) {
        if (hudget->isAt(toCrossHair) && hudget.get() != m_crossHair) {
            ObjectHudget* targetHudget = dynamic_cast<ObjectHudget*>(hudget.get());

            if (targetHudget) {
                if (!smallestTargetHudget) {
                    smallestTargetHudget = targetHudget;
                } else if (smallestTargetHudget->openingAngle() > targetHudget->openingAngle()) {
                    smallestTargetHudget = targetHudget;
                }
            } else {
                otherHudget = hudget.get();
            }
        }
    }

    if (smallestTargetHudget) {
        smallestTargetHudget->onClick(clickType);
    } else if (otherHudget) {
        otherHudget->onClick(clickType);
    }
}

glm::vec3 HUD::applyTo(const glm::vec3 &vertex) const {
    return position() + (orientation() * vertex);
}

void HUD::setTarget(WorldObject* target) {
    m_target = target ? target->handle<WorldObject>() : Handle<WorldObject>();
}

WorldObject* HUD::target() {
    return m_target.get();
}

float HUD::fovy() const {
    return m_fovy;
}

float HUD::fovx() const {
    return m_fovx;
}

void HUD::showMissionInfo(const std::string& title, const std::string& caption) {
    m_elements->showMissionInfo(title, caption);
}

void HUD::showMissionMessage(const std::string& message) {
    m_elements->showMissionMessage(message);
}

void HUD::showMessage(const std::string& message) {
    m_elements->showMessage(message);
}

void HUD::updateScanner(float deltaSec) {
    if (m_player->ship()) {
        m_scanner->update(deltaSec, m_player->ship());

        for (WorldObject* worldObject : m_scanner->foundWorldObjects()) {
            if (worldObject->info().showOnHud()) {
                ObjectHudget* objectHudget = new ObjectHudget(this);
                HUDObjectDelegate* objectDelgate = new HUDObjectDelegate(this, worldObject, objectHudget);
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

void HUD::updateFov() {
    assert(m_view);
    m_fovy = m_view->fovy() / 2;
    m_fovx = glm::atan(glm::tan(m_fovy) * m_view->aspectRatio());
}

void HUD::setView(const View* view) {
    m_view = view;
}

