#include "objecthudgetcornervoxels.h"

#include "utils/geometryhelper.h"

#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"

#include "objecthudget.h"
#include "objecthudgetvoxels.h"


ObjectHudgetCornerVoxels::ObjectHudgetCornerVoxels(ObjectHudgetVoxels* objectHudgetVoxels, const glm::ivec3& baseOffset, bool targetHightlight):
    VoxelCluster(targetHightlight ? 0.04f : 0.02f),
    m_objectHudgetVoxels(objectHudgetVoxels),
    m_baseOffset(baseOffset)
{
    int color = targetHightlight ? 0x99CCFF : 0x66AAFF;

    int edgeLength = 3;
    addVoxel(new Voxel(glm::ivec3(edgeLength, edgeLength, 0), color));
    transform().setCenter(glm::vec3(edgeLength, edgeLength, 0));

    for(int i = 1; i < edgeLength; i++) {
        addVoxel(new Voxel(glm::ivec3(-baseOffset.x * i + edgeLength, edgeLength, 0), color));
        addVoxel(new Voxel(glm::ivec3(edgeLength, baseOffset.y * i + edgeLength, 0), color));
    }
}

void ObjectHudgetCornerVoxels::draw() {
    ObjectHudget* objectHudget = m_objectHudgetVoxels->hudget();

    glm::vec3 euler = glm::vec3(-m_baseOffset.y, -m_baseOffset.x, 0) * (m_objectHudgetVoxels->openingAngle());
    glm::vec3 direction = GeometryHelper::quatFromViewDirection(objectHudget->localDirection()) * glm::quat(euler) * glm::vec3(0, 0, -1);

    transform().setPosition(objectHudget->worldPosition(direction));
    transform().setOrientation(objectHudget->worldOrientation(direction));

    VoxelRenderer::instance()->draw(*this);
}

