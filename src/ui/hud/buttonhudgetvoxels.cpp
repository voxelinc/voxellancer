#include "buttonhudgetvoxels.h"

#include "buttonhudget.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"


ButtonHudgetVoxels::ButtonHudgetVoxels(ButtonHudget* buttonHudget, std::string content, glm::vec3 direction, float scale) :
TextFieldHudgetVoxels(buttonHudget, content, direction, scale),
m_horizontalBounds(new VoxelCluster(scale)),
m_verticalBounds(new VoxelCluster(scale))
{
    setContent(content);
}

ButtonHudgetVoxels::~ButtonHudgetVoxels() = default;

void ButtonHudgetVoxels::updateBounds() {
    delete m_horizontalBounds;
    m_horizontalBounds = (new VoxelCluster(m_scale));
    delete m_verticalBounds;
    m_verticalBounds = (new VoxelCluster(m_scale));
    int width = (int)(m_width/m_scale)*m_content.size();
    int height = (int)(m_height/m_scale)*2;
    for (int i = 0; i < width; i++) {
        m_horizontalBounds->addVoxel(new Voxel(glm::ivec3(i, 0, 0), 0x0FF00F));
    }
    for (int i = 0; i < height; i++) {
        m_verticalBounds->addVoxel(new Voxel(glm::ivec3(0, i, 0), 0x0FF00F));
    }
}

void ButtonHudgetVoxels::draw() {
    TextFieldHudgetVoxels::draw();
    m_horizontalBounds->transform().setPosition(upperLeft());
    m_horizontalBounds->transform().setOrientation(m_hudget->worldOrientation(m_direction));
    VoxelRenderer::instance()->draw(*m_horizontalBounds);
    m_horizontalBounds->transform().setPosition(lowerLeft());
    m_horizontalBounds->transform().setOrientation(m_hudget->worldOrientation(m_direction));
    VoxelRenderer::instance()->draw(*m_horizontalBounds);
    m_verticalBounds->transform().setPosition(lowerLeft());
    m_verticalBounds->transform().setOrientation(m_hudget->worldOrientation(m_direction));
    VoxelRenderer::instance()->draw(*m_verticalBounds);
    m_verticalBounds->transform().setPosition(lowerRight());
    m_verticalBounds->transform().setOrientation(m_hudget->worldOrientation(m_direction));
    VoxelRenderer::instance()->draw(*m_verticalBounds);
}

void ButtonHudgetVoxels::setContent(std::string content) {
    if (m_content.compare(content) == 0) {
        return;
    }
    TextFieldHudgetVoxels::setContent(content);
    updateBounds();
}