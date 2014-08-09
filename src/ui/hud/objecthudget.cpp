#include "objecthudget.h"

#include <cmath>

#include <glm/glm.hpp>

#include "ai/character.h"

#include "display/viewer.h"
#include "display/view.h"

#include "factions/factionrelation.h"
#include "factions/factionmatrix.h"

#include "ui/hud/textfieldhudget.h"

#include "utils/geometryhelper.h"
#include "utils/safenormalize.h"

#include "world/world.h"

#include "worldobject/worldobjectinfo.h"
#include "worldobject/worldobject.h"
#include "worldobject/ship.h"

#include "player.h"

#include "hudobjectdelegate.h"
#include "hud.h"
#include "voxel/voxelclusterbounds.h"
#include "hudobjectdelegate.h"
#include "objecthudgetvoxels.h"
#include "arrowhudgetvoxels.h"



ObjectHudget::ObjectHudget(HUD* hud):
    Hudget(hud),
    m_objectDelegate(nullptr),
    m_objectVoxels(new ObjectHudgetVoxels(this)),
    m_arrowVoxels(new ArrowHudgetVoxels(this)),
    m_shieldLabel(new TextFieldHudget(hud, glm::vec3(), 0.010f))
{
    m_insideFov = false;
}

ObjectHudget::~ObjectHudget() = default;

void ObjectHudget::update(float deltaSec) {
    updateTargeted();
    updateFov();
    m_insideFov = isInsideFov();
    bool targetHighlight = false;
    FactionRelationType relationType = FactionRelationType::Neutral;
    WorldObject* worldObject = m_objectDelegate->worldObject();
    if(worldObject) {
        calculateOpeningAngle();
        pointToWorldPoint(worldObject->transform().position());

        if(m_hud->player()->ship()) {
            if(worldObject == m_hud->player()->ship()->targetObject()) {
                targetHighlight = true;
            }
            // TODO: Replace the following two lines with proper WorldObjectType mechanism
            Ship* ship = dynamic_cast<Ship*>(worldObject);
            if (ship) {
                relationType = ship->character()->relationTypeTo(m_hud->player()->ship());
            }
        }
    }
    if (!m_insideFov) {
        m_arrowVoxels->updateDirection(closestPointInsideFov());
    }

    m_objectVoxels->setTargetHightlight(targetHighlight);
    m_objectVoxels->setRelationType(relationType);
    m_objectVoxels->update(deltaSec);
}

void ObjectHudget::draw() {
    m_objectVoxels->draw();

    if (!m_insideFov) {
        m_arrowVoxels->draw();
    }

    WorldObject* worldObject = m_objectDelegate->worldObject();
    if(worldObject) {
        glm::vec3 euler = glm::vec3(-1.2, -1, 0) * (m_objectVoxels->openingAngle());
        glm::vec3 direction = GeometryHelper::quatFromViewDirection(localDirection()) * glm::quat(euler) * glm::vec3(0, 0, -1);

        m_shieldLabel->setDirection(direction);
        m_shieldLabel->setText(worldObject->info().shieldStatus());
        m_shieldLabel->draw();
    }
}

void ObjectHudget::calculateOpeningAngle() {
    WorldObject* worldObject = m_objectDelegate->worldObject();

    float radius = worldObject->bounds().sphere().radius();
    float distance = glm::length(m_hud->centerOfView() - worldObject->transform().position());
    float alpha = std::atan2(radius, distance) * 0.95f;

    alpha = std::max(alpha, 0.04f); // Hack, set minimum size

    m_objectVoxels->setOpeningAngle(alpha);
}

HUDObjectDelegate* ObjectHudget::objectDelegate() {
    return m_objectDelegate;
}

void ObjectHudget::setObjectDelegate(HUDObjectDelegate* objectDelegate) {
    m_objectDelegate = objectDelegate;
}

bool ObjectHudget::isAt(const Ray& ray) const {
    if (!m_insideFov) {
        return m_arrowVoxels->isAt(ray) || m_objectVoxels->isAt(ray);
    }
    return m_objectVoxels->isAt(ray);
}

bool ObjectHudget::isInsideFov() {
    float angleCorrection = 0.0f;
    if (localDirection().z > 0) {
        angleCorrection = glm::radians(90.0f); //angle between vector and plane is always <= 90 deg, adding 90 deg for targets behind player
    }
    if (GeometryHelper::angleBetweenVectorPlane(localDirection(), glm::vec3(0, 1, 0)) + angleCorrection < m_fovy &&
        GeometryHelper::angleBetweenVectorPlane(localDirection(), glm::vec3(1, 0, 0)) + angleCorrection < m_fovx) {
        return true;
    }
    return false;
}

glm::vec3 ObjectHudget::closestPointInsideFov() {
    glm::vec3 planeNormalX(glm::cos(m_fovx), 0, glm::cos(glm::radians(90.0f) - m_fovx));
    glm::vec3 planeNormalY(0, glm::cos(m_fovy), glm::cos(glm::radians(90.0f) - m_fovy));
    glm::vec3 planeDirection(glm::abs(localDirection().y), -glm::abs(localDirection().x), 0);

    glm::vec3 intersectionX = glm::cross(planeNormalX, planeDirection);
    glm::vec3 intersectionY = glm::cross(planeNormalY, planeDirection);
    float angleX = GeometryHelper::angleBetween(intersectionX, glm::vec3(0, 0, -1));
    float angleY = GeometryHelper::angleBetween(intersectionY, glm::vec3(0, 0, -1));

    glm::vec3 pointInsideFov;

    if (angleX < angleY) {
        assert(normalizeable(intersectionX));
        pointInsideFov = glm::normalize(intersectionX);
    } else {
        assert(normalizeable(intersectionY));
        pointInsideFov = glm::normalize(intersectionY);
    }

    pointInsideFov.x = glm::abs(pointInsideFov.x);
    pointInsideFov.y = glm::abs(pointInsideFov.y);
    pointInsideFov.z = -glm::abs(pointInsideFov.z);

    if (localDirection().x < 0) {
        pointInsideFov.x *= -1;
    }

    if (localDirection().y < 0) {
        pointInsideFov.y *= -1;
    }

    return pointInsideFov;
}

void ObjectHudget::onClick(ClickType clickType) {
    if (clickType == ClickType::Selection) {
        WorldObject* worldObject = m_objectDelegate->worldObject();
        if (worldObject && worldObject->info().canLockOn()) {
            m_hud->player()->setTarget(worldObject);
        }
    }
}

float ObjectHudget::openingAngle() const {
    return m_objectVoxels->openingAngle();
}

void ObjectHudget::updateTargeted() {
    bool currentlyTargeted = m_hud->target() == m_objectDelegate->worldObject();
    if (m_targeted != currentlyTargeted) {
        m_targeted = currentlyTargeted;
        m_arrowVoxels->setTargeted(m_targeted);
    }
}

void ObjectHudget::updateFov() {
    m_fovy = m_hud->fovy()*0.97f;
    m_fovx = m_hud->fovx()*0.98f;
}

