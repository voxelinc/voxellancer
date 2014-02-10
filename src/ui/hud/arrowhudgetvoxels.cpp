#include "arrowhudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

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
    m_arrow.transform().setPosition(m_hudget->worldPosition(m_targetPoint));
    m_arrow.transform().setOrientation(m_hudget->worldOrientation());

    VoxelRenderer::instance()->draw(&m_arrow);
}

void ArrowHudgetVoxels::calculateAngles() {
    float maxAngleX = glm::radians(40.0f);
    float maxAngleY = glm::radians(25.0f);

    float angleX = angleToPlane(glm::vec3(1.0f,0.0f,0.0f));
    float angleY = angleToPlane(glm::vec3(0.0f, 1.0f, 0.0f));

    m_targetPoint = m_hudget->localDirection();

    if (angleX > maxAngleX) {
        float angleDiff = maxAngleX - angleX;
        if (m_hudget->localDirection().x < 0) {
            angleDiff *= -1;
        }
        printf("x ");
        //printf(" diffx = %f\n", glm::degrees(angleDiff));
        glm::vec3 tmp = glm::axis(glm::angleAxis(angleDiff, glm::vec3(1.0f, 0.0f, 0.0f)));
        float actualAngle = glm::angle(glm::angleAxis(angleDiff, glm::vec3(1.0f, 0.0f, 0.0f)));
        //printf("x: %f y: %f z: %f \n", tmp.x, tmp.y, tmp.z);
        //printf("angle: %f actual %f\n", angleDiff, actualAngle);
        m_targetPoint = m_targetPoint *  glm::angleAxis(angleDiff, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (angleY > maxAngleY) {
        printf("y ");
        float angleDiff = maxAngleY - angleY;
        if (m_hudget->localDirection().y > 0) {
            angleDiff *= -1;
        }
        m_targetPoint = m_targetPoint * glm::angleAxis(angleDiff, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    printf("\n");
    return;

}


float ArrowHudgetVoxels::angleToPlane(glm::vec3 planeNormal) {
    float angle = glm::asin(glm::abs(glm::dot(planeNormal, m_hudget->localDirection())) / glm::length(m_hudget->localDirection()));
    if (m_hudget->localDirection().z > 0) {
        angle = glm::radians(180.0f) - angle;
    }
    return angle;
}
