#include "buttonhudgetvoxels.h"

#include "buttonhudget.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"


ButtonHudgetVoxels::ButtonHudgetVoxels(ButtonHudget* buttonHudget, std::string content, glm::vec3 direction, float scale) :
TextFieldHudgetVoxels(buttonHudget, content, direction, scale),
m_buttonVoxels(new VoxelCluster(scale))
{
    setContent(content);
}

ButtonHudgetVoxels::~ButtonHudgetVoxels() = default;

void ButtonHudgetVoxels::updateBounds() {
    delete m_buttonVoxels;
    m_buttonVoxels = (new VoxelCluster(m_scale));
    int width = (int)(m_width/m_scale)*m_content.size()+1;
    int height = (int)(m_height/m_scale)*2+1;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
                m_buttonVoxels->addVoxel(new Voxel(glm::ivec3(i, j, 0), 0x0FF00F));
            } else {
                // draw only bounds
            }
        }
    }
}

void ButtonHudgetVoxels::draw() {
    m_buttonVoxels->transform().setPosition(lowerLeft());
    m_buttonVoxels->transform().setOrientation(m_hudget->worldOrientation(m_direction));
    VoxelRenderer::instance()->draw(*m_buttonVoxels);
    TextFieldHudgetVoxels::draw();
}

void ButtonHudgetVoxels::setContent(std::string content) {
    if (m_content.compare(content) == 0) {
        return;
    }
    TextFieldHudgetVoxels::setContent(content);
    updateBounds();
}