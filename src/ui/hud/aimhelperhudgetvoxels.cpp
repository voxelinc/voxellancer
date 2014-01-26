#include "aimhelperhudgetvoxels.h"

#include "voxel/voxelrenderer.h"

#include "aimhelperhudget.h"


AimHelperHudgetVoxels::AimHelperHudgetVoxels(AimHelperHudget* aimHelperHudget):
    m_aimHelperHudget(aimHelperHudget),
    m_dot(1.0f)
{
    int color = 0xFFAA00;
    m_dot.addVoxel(new Voxel(glm::ivec3(0, 0, 0), color));
}

void AimHelperHudgetVoxels::draw() {
    m_dot.transform().setPosition(m_aimHelperHudget->position());
    m_dot.transform().setOrientation(m_aimHelperHudget->orientation());
    VoxelRenderer::instance()->draw(&m_dot);
}

