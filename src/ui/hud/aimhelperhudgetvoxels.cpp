#include "aimhelperhudgetvoxels.h"

#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"

#include "aimhelperhudget.h"
#include "voxel/voxelcluster.h"


AimHelperHudgetVoxels::AimHelperHudgetVoxels(AimHelperHudget* aimHelperHudget):
    m_aimHelperHudget(aimHelperHudget),
    m_dot(new VoxelCluster(0.04f)),
    m_circle(new VoxelCluster(0.04f))
{
    int color = 0xFFAA00;
    int radius = 5;
    int diameter = radius * 2;

    m_dot->addVoxel(new Voxel(glm::ivec3(0, 0, 0), color));

    m_circle->transform().setCenter(glm::vec3(radius, radius, 0));
    for(int x = 0; x < diameter; x++) {
        for(int y = 0; y < diameter; y++) {
            float distance = glm::length(glm::vec2(x, y) - glm::vec2(radius, radius));
            if(glm::abs((radius-1) - distance) < 0.3f) {
                m_circle->addVoxel(new Voxel(glm::ivec3(x, y, 0), color));
            }
        }
    }
}

AimHelperHudgetVoxels::~AimHelperHudgetVoxels() = default;

void AimHelperHudgetVoxels::draw() {
    m_dot->transform().setPosition(m_aimHelperHudget->worldPosition());
    m_dot->transform().setOrientation(m_aimHelperHudget->worldOrientation());

    m_circle->transform().setPosition(m_aimHelperHudget->worldPosition());
    m_circle->transform().setOrientation(m_aimHelperHudget->worldOrientation());

    VoxelRenderer::instance()->draw(*m_dot);
    VoxelRenderer::instance()->draw(*m_circle);
}


