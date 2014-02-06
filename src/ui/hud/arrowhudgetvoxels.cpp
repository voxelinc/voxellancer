#include "arrowhudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>

#include "utils/geometryhelper.h"

#include "voxel/voxelrenderer.h"

#include "hud.h"
#include "ArrowHudget.h"
#include "voxel/voxelcluster.h"

ArrowHudgetVoxels::ArrowHudgetVoxels(ArrowHudget* hudget) :
    m_hudget(hudget),
    m_arrow(0.05f)
{
    int edgeLength = 5;
    m_arrow.addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFF0000));
    for (int i = 1; i < edgeLength; i++) {
        m_arrow.addVoxel(new Voxel(glm::ivec3(i, 0, 0), 0xFF0000));
        m_arrow.addVoxel(new Voxel(glm::ivec3(0, i, 0), 0xFF0000));
    }
    for (int i = 1; i < edgeLength - 1; i++) {
        for (int j = 1; j < edgeLength - i; j++) {
            m_arrow.addVoxel(new Voxel(glm::ivec3(i, j, 0), 0xFFFF00));
        }
    }
}

ArrowHudgetVoxels::~ArrowHudgetVoxels() {
}

ArrowHudget* ArrowHudgetVoxels::hudget() {
    return m_hudget;
}

void ArrowHudgetVoxels::draw() {
    calculateAngles();
    m_arrow.transform().setPosition(m_hudget->worldPosition());
    m_arrow.transform().setOrientation(m_hudget->worldOrientation());

    VoxelRenderer::instance()->draw(&m_arrow);
}

void ArrowHudgetVoxels::calculateAngles() {
    float maxAngleX = 45;
    float maxAngleY = 30;

    glm::vec3 lookAt(0, 0, -1.0f);

    glm::vec3 vecX(m_hudget->localDirection().x, 0, m_hudget->localDirection().z);
    glm::vec3 vecY(0, m_hudget->localDirection().y, m_hudget->localDirection().z);

    m_angleX = glm::degrees(glm::acos(glm::dot(vecX, lookAt) / (glm::length(vecX) * glm::length(lookAt))));
    m_angleY = glm::degrees(glm::acos(glm::dot(vecY, lookAt) / (glm::length(vecY) * glm::length(lookAt))));

    if (m_angleX < maxAngleX)
        return;

    float lengthX = glm::length(m_hudget->localDirection());
    float lengthY = glm::length(m_hudget->localDirection());

    glm::vec3 distanceX = glm::normalize(vecX) - lookAt;
    glm::vec3 distanceY = glm::normalize(vecY) - lookAt;

    distanceX *= maxAngleX / m_angleX;
    distanceY *= maxAngleX / m_angleX;

    glm::vec3 targetX = glm::normalize(lookAt + distanceX);
    glm::vec3 targetY = glm::normalize(lookAt + distanceY);

    printf("x: %f y: %f\r", m_angleX, m_angleY);
}
