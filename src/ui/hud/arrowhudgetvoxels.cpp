#include "arrowhudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "utils/geometryhelper.h"

#include "resource/clustercache.h"

#include "voxel/voxelrenderer.h"

#include "hud.h"
#include "ArrowHudget.h"
#include "voxel/voxelcluster.h"

ArrowHudgetVoxels::ArrowHudgetVoxels(ArrowHudget* hudget) :
    m_hudget(hudget),
    m_arrow(0.01f),
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
    if (!findPoint()) {
        return;
    }
    m_arrow.transform().setOrientation(m_hudget->worldOrientation(m_targetPoint)*glm::angleAxis(glm::atan(m_targetPoint.x, m_targetPoint.y), glm::vec3(0, 0, -1)));
    m_arrow.transform().setPosition(m_hudget->worldPosition(m_targetPoint));
    VoxelRenderer::instance()->draw(&m_arrow);
}

bool ArrowHudgetVoxels::findPoint() {
    glm::vec3 lookat(0.0f, 0.0f, -1.0f);
    glm::vec3 direction = m_hudget->localDirection();
    direction.z = -glm::abs(direction.z);
    glm::vec3 diff = direction - lookat;
    if (glm::length(diff) < prop_arrowDistance.get() && m_hudget->localDirection().z < 0) {
        return false;
    }
    diff = glm::normalize(diff);
    glm::vec3 point = lookat + diff*prop_arrowDistance.get();
    m_targetPoint = glm::normalize(point);
    return true;
}