#include "objecthudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>

#include "utils/geometryhelper.h"

#include "voxel/voxelrenderer.h"

#include "hud.h"
#include "objecthudget.h"
#include "objecthudgetcornervoxels.h"


ObjectHudgetVoxels::ObjectHudgetVoxels(ObjectHudget* hudget):
    m_hudget(hudget),
    m_openingAngle(0.0f),
    m_targetHightlight(false)
{
    setupCorners();
}

ObjectHudgetVoxels::~ObjectHudgetVoxels() {

}

ObjectHudget* ObjectHudgetVoxels::hudget() {
    return m_hudget;
}

void ObjectHudgetVoxels::setTargetHightlight(bool targetHightlight) {
    m_targetHightlight = targetHightlight;
}

float ObjectHudgetVoxels::openingAngle() const {
    return m_openingAngle;
}

void ObjectHudgetVoxels::setOpeningAngle(float openingAngle) {
    m_openingAngle = openingAngle;
}

void ObjectHudgetVoxels::draw() {
    int index = m_targetHightlight ? 1 : 0;

    m_lu[index]->draw();
    m_lb[index]->draw();
    m_ru[index]->draw();
    m_rb[index]->draw();
}

void ObjectHudgetVoxels::setupCorners() {
    m_lu[0].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, 1, 0), false));
    m_lb[0].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, -1, 0), false));
    m_ru[0].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, 1, 0), false));
    m_rb[0].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, -1, 0), false));

    m_lu[1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, 1, 0), true));
    m_lb[1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, -1, 0), true));
    m_ru[1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, 1, 0), true));
    m_rb[1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, -1, 0), true));
}

