#include "arrowhudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "utils/geometryhelper.h"

#include "resource/clustercache.h"

#include "voxel/voxelrenderer.h"

#include "hud.h"
#include "arrowhudget.h"
#include "voxel/voxelcluster.h"

ArrowHudgetVoxels::ArrowHudgetVoxels(ArrowHudget* hudget) :
    m_hudget(hudget),
    m_arrow(0.025f),
    prop_arrowDistance("hud.arrowDistance")
{
    ClusterCache::instance()->fillCluster(&m_arrow, "data/hud/arrowXT.csv");
}

ArrowHudgetVoxels::~ArrowHudgetVoxels() {
}

ArrowHudget* ArrowHudgetVoxels::hudget() {
    return m_hudget;
}

void ArrowHudgetVoxels::draw() {
    if (findPointOnEdge()) {
        m_arrow.transform().setOrientation(m_hudget->worldOrientation(m_targetPoint)*glm::angleAxis(glm::atan(m_targetPoint.x, m_targetPoint.y), glm::vec3(0, 0, -1)));
        m_arrow.transform().setPosition(m_hudget->worldPosition(m_targetPoint));
        VoxelRenderer::instance()->draw(&m_arrow);
    }
}

bool ArrowHudgetVoxels::findPoint() {
    glm::vec3 lookat(0.0f, 0.0f, -1.0f);
    glm::vec3 direction = m_hudget->localDirection();
    direction.z = -glm::abs(direction.z);
    glm::vec3 diff = direction - lookat;
    if (glm::length(diff) < prop_arrowDistance.get() && m_hudget->localDirection().z < 0) {
        return false;
    }
    diff.z = 0;
    diff = glm::normalize(diff)*prop_arrowDistance.get();
    diff.z = -1;
    m_targetPoint = diff;
    return true;
}

bool ArrowHudgetVoxels::findPointOnEdge() {
    float edgeAngleX = glm::radians(40.0f);
    float edgeAngleY = glm::radians(28.0f);
    if (vectorAngleToPlane(m_hudget->localDirection(), glm::vec3(0, 1, 0)) < edgeAngleY &&
        vectorAngleToPlane(m_hudget->localDirection(), glm::vec3(1, 0, 0)) < edgeAngleX) {
        return false;
    }
    glm::vec3 planeNormalX(glm::cos(edgeAngleX), 0, glm::cos(glm::radians(90.0f) - edgeAngleX));
    glm::vec3 planeNormalY(0, glm::cos(edgeAngleY), glm::cos(glm::radians(90.0f) - edgeAngleY));
    glm::vec3 planeDirection(glm::abs(m_hudget->localDirection().y), -glm::abs(m_hudget->localDirection().x), 0);

    glm::vec3 intersectionX = glm::cross(planeNormalX, planeDirection);
    glm::vec3 intersectionY = glm::cross(planeNormalY, planeDirection);
    float angleX = vectorAngleToVector(intersectionX, glm::vec3(0, 0, -1));
    float angleY = vectorAngleToVector(intersectionY, glm::vec3(0, 0, -1));

    if (angleX < angleY) {
        m_targetPoint = glm::normalize(intersectionX);
    } else {
        m_targetPoint = glm::normalize(intersectionY);
    }
    m_targetPoint.x = glm::abs(m_targetPoint.x);
    m_targetPoint.y = glm::abs(m_targetPoint.y);
    m_targetPoint.z = glm::abs(m_targetPoint.z)*-1;
    if (m_hudget->localDirection().x < 0) {
        m_targetPoint.x *= -1;
    }
    if (m_hudget->localDirection().y < 0) {
        m_targetPoint.y *= -1;
    }
    return true;
}

float ArrowHudgetVoxels::vectorAngleToPlane(glm::vec3 vector, glm::vec3 planeNormal) {
    return glm::asin(glm::abs(glm::dot(planeNormal, vector)) / glm::length(planeNormal)*glm::length(vector));
}

float ArrowHudgetVoxels::vectorAngleToVector(glm::vec3 vector, glm::vec3 vector2) {
    return glm::acos(glm::dot(vector, vector2) / glm::length(vector)*glm::length(vector2));
}

