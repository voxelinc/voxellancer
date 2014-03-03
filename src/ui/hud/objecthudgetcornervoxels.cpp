#include "objecthudgetcornervoxels.h"

#include "utils/geometryhelper.h"

#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"

#include "objecthudget.h"
#include "objecthudgetvoxels.h"


ObjectHudgetCornerVoxels::ObjectHudgetCornerVoxels(ObjectHudgetVoxels* objectHudgetVoxels, const glm::ivec3& baseOffset):
    m_objectHudgetVoxels(objectHudgetVoxels),
    m_baseOffset(baseOffset)
{
    m_voxelClusters.resize(10);

    float normalScale = 0.02f;
    float highlightScale = 0.04f;

    addIndex(0, 0xFF0000, normalScale);
    addIndex(1, 0xFF0000, highlightScale);
    addIndex(2, 0xCC6600, normalScale);
    addIndex(3, 0xCC6600, highlightScale);
    addIndex(4, 0x66AAFF, normalScale);
    addIndex(5, 0x66AAFF, highlightScale);
    addIndex(6, 0x33AA00, normalScale);
    addIndex(7, 0x33AA00, highlightScale);
    addIndex(8, 0x11CC00, normalScale);
    addIndex(9, 0x11CC00, highlightScale);
}

const glm::vec3& ObjectHudgetCornerVoxels::position() const {
    return m_position;
}

const glm::quat& ObjectHudgetCornerVoxels::orientation() const {
    return m_orientation;
}

void ObjectHudgetCornerVoxels::update(float deltaSec) {
    ObjectHudget* objectHudget = m_objectHudgetVoxels->hudget();

    glm::vec3 euler = glm::vec3(-m_baseOffset.y, -m_baseOffset.x, 0) * (m_objectHudgetVoxels->openingAngle());
    glm::vec3 direction = GeometryHelper::quatFromViewDirection(objectHudget->localDirection()) * glm::quat(euler) * glm::vec3(0, 0, -1);

    m_position = objectHudget->worldPosition(direction);
    m_orientation = objectHudget->worldOrientation(direction);
}

void ObjectHudgetCornerVoxels::draw(int index) {
    m_voxelClusters[index]->transform().setPosition(m_position);
    m_voxelClusters[index]->transform().setOrientation(m_orientation);

    VoxelRenderer::instance()->draw(*m_voxelClusters[index].get());
}

void ObjectHudgetCornerVoxels::addIndex(int index, uint32_t color, float scale) {
    VoxelCluster* voxelCluster = new VoxelCluster(scale);

    int edgeLength = 3;
    voxelCluster->addVoxel(new Voxel(glm::ivec3(edgeLength, edgeLength, 0), color));
    voxelCluster->transform().setCenter(glm::vec3(edgeLength, edgeLength, 0));

    for(int i = 1; i < edgeLength; i++) {
        voxelCluster->addVoxel(new Voxel(glm::ivec3(-m_baseOffset.x * i + edgeLength, edgeLength, 0), color));
        voxelCluster->addVoxel(new Voxel(glm::ivec3(edgeLength, m_baseOffset.y * i + edgeLength, 0), color));
    }

    m_voxelClusters[index].reset(voxelCluster);
}

