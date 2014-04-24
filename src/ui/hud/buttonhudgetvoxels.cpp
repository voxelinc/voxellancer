#include "buttonhudgetvoxels.h"

#include "buttonhudget.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxel.h"
#include "voxel/voxelrenderer.h"
#include "hud.h"


ButtonHudgetVoxels::ButtonHudgetVoxels(ButtonHudget* buttonHudget, glm::vec3 direction, TextOrientation textOrientation, float scale, std::string content, FontSize fontSize, ButtonStyle buttonStyle) :
TextFieldHudgetVoxels(buttonHudget, direction, textOrientation, scale, content, fontSize),
    m_buttonVoxels(new VoxelCluster(scale)),
    m_buttonStyle(buttonStyle),
    m_hudget(buttonHudget)
{
    setText(content);
}

ButtonHudgetVoxels::~ButtonHudgetVoxels() = default;

void ButtonHudgetVoxels::updateBounds() {
    if (m_buttonStyle == ButtonStyle::PLAIN) {
        return;
    }
    m_buttonVoxels.reset(new VoxelCluster(m_scale));
    int width = (int)(m_width/m_scale)*m_text.size()+1;
    int height = (int)(m_height/m_scale)*2;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
                m_buttonVoxels->addVoxel(new Voxel(glm::ivec3(i, j, 0), 0x0FF00F));
            } else if (m_buttonStyle == ButtonStyle::BORDERED_FILLED) {
                m_buttonVoxels->addVoxel(new Voxel(glm::ivec3(i, j, 1), 0x17012D));
            }
        }
    }
}

void ButtonHudgetVoxels::draw() {
    if (m_buttonStyle == ButtonStyle::BORDERED || m_buttonStyle == ButtonStyle::BORDERED_FILLED) {
        switch (textOrientation()) {
        case TextOrientation::BACKWARDS:
            m_buttonVoxels->transform().setPosition(lowerRight());
            m_buttonVoxels->transform().setOrientation(m_hudget->hud()->orientation());
            m_buttonVoxels->transform().rotate(glm::angleAxis(glm::pi<float>(), glm::vec3(0, 1, 0)));
            break;
        case TextOrientation::SPHERE_STRAIGHT:
            m_buttonVoxels->transform().setPosition(lowerRight());
            m_buttonVoxels->transform().setOrientation(m_hudget->worldOrientation(TextFieldHudgetVoxels::m_direction));
            m_buttonVoxels->transform().rotate(glm::angleAxis(glm::pi<float>(), glm::vec3(0, 1, 0)));
            break;
        }
        VoxelRenderer::instance()->draw(*m_buttonVoxels);
    }
    TextFieldHudgetVoxels::draw();
}

void ButtonHudgetVoxels::setText(const std::string& text) {
    if (m_text.compare(text) == 0) {
        return;
    }
    TextFieldHudgetVoxels::setText(text);
    updateBounds();
}

ButtonStyle ButtonHudgetVoxels::buttonStyle() {
    return m_buttonStyle;
}

void ButtonHudgetVoxels::setButtonStyle(ButtonStyle buttonStyle) {
    m_buttonStyle = buttonStyle;
}