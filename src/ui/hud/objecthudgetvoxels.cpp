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
    m_targetHightlight(false),
    m_relationType(FactionRelationType::Neutral)
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

void ObjectHudgetVoxels::setRelationType(FactionRelationType relationType) {
    m_relationType = relationType;
}

float ObjectHudgetVoxels::openingAngle() const {
    return m_openingAngle;
}

void ObjectHudgetVoxels::setOpeningAngle(float openingAngle) {
    m_openingAngle = openingAngle;
}

void ObjectHudgetVoxels::draw() {
    int index = 2 * ((int)m_relationType) + (m_targetHightlight ? 1 : 0) ;

    m_lu[index]->draw();
    m_lb[index]->draw();
    m_ru[index]->draw();
    m_rb[index]->draw();
}

void ObjectHudgetVoxels::setupCorners() {
    addCornerSet(0, 0xFF0000);
    addCornerSet(1, 0xCC6600);
    addCornerSet(2, 0x66AAFF);
    addCornerSet(3, 0x33AA00);
    addCornerSet(4, 0x11CC00);
}

void ObjectHudgetVoxels::addCornerSet(int index, uint32_t color) {
    m_lu[index*2].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, 1, 0), color, false));
    m_lb[index*2].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, -1, 0), color, false));
    m_ru[index*2].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, 1, 0), color, false));
    m_rb[index*2].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, -1, 0), color, false));

    m_lu[index*2+1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, 1, 0), color, true));
    m_lb[index*2+1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, -1, 0), color, true));
    m_ru[index*2+1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, 1, 0), color, true));
    m_rb[index*2+1].reset(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, -1, 0), color, true));
}

