#include "objecthudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/intersect.hpp>

#include "utils/geometryhelper.h"
#include "voxel/voxelrenderer.h"

#include "geometry/ray.h"

#include "hud.h"
#include "objecthudget.h"

#include "objecthudgetcornervoxels.h"


ObjectHudgetVoxels::ObjectHudgetVoxels(ObjectHudget* hudget):
    m_hudget(hudget),
    m_openingAngle(0.0f),
    m_targetHightlight(false),
    m_relationType(FactionRelationType::Neutral),
    m_lu(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, 1, 0))),
    m_lb(new ObjectHudgetCornerVoxels(this, glm::ivec3(-1, -1, 0))),
    m_ru(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, 1, 0))),
    m_rb(new ObjectHudgetCornerVoxels(this, glm::ivec3(1, -1, 0)))
{
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

void ObjectHudgetVoxels::update(float deltaSec) {
    m_lu->update(deltaSec);
    m_lb->update(deltaSec);
    m_ru->update(deltaSec);
    m_rb->update(deltaSec);
}

void ObjectHudgetVoxels::draw() {
    int index = 2 * ((int)m_relationType) + (m_targetHightlight ? 1 : 0) ;

    m_lu->draw(index);
    m_lb->draw(index);
    m_ru->draw(index);
    m_rb->draw(index);
}

bool ObjectHudgetVoxels::isAt(const Ray& ray) const {
    int index = 2 * ((int)m_relationType) + (m_targetHightlight ? 1 : 0);
    return GeometryHelper::intersectRectangle(&ray, m_lu[index * 2].get()->position(), m_ru[index * 2].get()->position(), m_rb[index * 2].get()->position(), m_lb[index * 2].get()->position());
}

