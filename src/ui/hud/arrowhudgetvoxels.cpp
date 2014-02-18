#include "arrowhudgetvoxels.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "utils/geometryhelper.h"

#include "resource/clustercache.h"

#include "voxel/voxelcluster.h"
#include "voxel/voxelrenderer.h"

#include "hud.h"
#include "objecthudget.h"


ArrowHudgetVoxels::ArrowHudgetVoxels(ObjectHudget* hudget) :
    m_hudget(hudget),
    m_arrow(0.025f),
    prop_arrowDistance("hud.arrowDistance")
{
    ClusterCache::instance()->fillCluster(&m_arrow, "data/hud/arrowXT.csv");
    m_arrow.transform().setCenter(glm::vec3(4, 7, 0));
}

ArrowHudgetVoxels::~ArrowHudgetVoxels() {
}

ObjectHudget* ArrowHudgetVoxels::hudget() {
    return m_hudget;
}

void ArrowHudgetVoxels::draw() {
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
    diff.z = 0;
    diff = glm::normalize(diff)*prop_arrowDistance.get();
    diff.z = -1;
    m_targetPoint = diff;
    return true;
}

void ArrowHudgetVoxels::updateDirection(glm::vec3 direction) {
    m_arrow.transform().setPosition(m_hudget->worldPosition(direction));
    m_arrow.transform().setOrientation(m_hudget->worldOrientation(direction)*glm::angleAxis(glm::atan(direction.x, direction.y), glm::vec3(0, 0, -1)));
}

void ArrowHudgetVoxels::setTargeted(bool targeted) {
    if (targeted) {
        m_arrow.transform().setScale(0.05f);
    } else {
        m_arrow.transform().setScale(0.025f);
    }
}

bool ArrowHudgetVoxels::isAt(const Ray& ray) const {
    return ray.intersects(m_arrow.bounds().sphere());
}
