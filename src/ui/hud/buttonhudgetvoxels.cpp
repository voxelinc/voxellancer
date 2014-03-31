#include "buttonhudgetvoxels.h"

#include "buttonhudget.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"


ButtonHudgetVoxels::ButtonHudgetVoxels(ButtonHudget* buttonHudget, glm::vec3 direction, float scale, std::string content, FontSize fontSize, bool bounds) :
    TextFieldHudgetVoxels(buttonHudget, direction, scale, content, fontSize),
    m_buttonVoxels(new VoxelCluster(scale)),
    m_bounds(bounds),
    m_hudget(buttonHudget)
{
    setContent(content);
}

ButtonHudgetVoxels::~ButtonHudgetVoxels() = default;

void ButtonHudgetVoxels::updateBounds() {
    m_buttonVoxels.reset(new VoxelCluster(m_scale));
    int width = (int)(m_width/m_scale)*m_content.size()+1;
    int height = (int)(m_height/m_scale)*2;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
                m_buttonVoxels->addVoxel(new Voxel(glm::ivec3(i, j, 0), 0x0FF00F));
            } else {
                m_buttonVoxels->addVoxel(new Voxel(glm::ivec3(i, j, 1), 0x17012D));
            }
        }
    }
}

void ButtonHudgetVoxels::draw() {
    if (m_bounds) {
        m_buttonVoxels->transform().setPosition(lowerRight());
        m_buttonVoxels->transform().setOrientation(m_hudget->worldOrientation(TextFieldHudgetVoxels::m_direction));
        m_buttonVoxels->transform().rotate(glm::angleAxis(glm::pi<float>(), glm::vec3(0, 1, 0)));
        VoxelRenderer::instance()->draw(*m_buttonVoxels);
    }
    TextFieldHudgetVoxels::draw();
}

void ButtonHudgetVoxels::setContent(std::string content) {
    if (m_content.compare(content) == 0) {
        return;
    }
    TextFieldHudgetVoxels::setContent(content);
    updateBounds();
}