#include "targetguide.h"

#include "voxel/voxelrenderer.h"


TargetGuideArrowVoxels::TargetGuideArrowVoxels(TargetGuideArrow* arrow):
    VoxelCluster(0.05f),
    m_arrow(arrow)
{
    int length = 3;
    int color = 0xFF0000;

    transform().setCenter(glm::vec3(length/2, length/2, 0));

    addVoxel(new Voxel(glm::ivec3(length-1, length, 0), color));

    int yDiff = 1;
    for(int x = length - 2; x >= 0; x--) {
        addVoxel(new Voxel(glm::ivec3(x, length - yDiff, 0), color));
        addVoxel(new Voxel(glm::ivec3(x, length + yDiff, 0), color));
        yDiff++;
    }
}

void TargetGuideArrowVoxels::draw() {
    transform().setPosition(m_arrow->position());
    transform().setOrientation(m_arrow->orientation());

    VoxelRenderer::instance()->draw(this);
}

