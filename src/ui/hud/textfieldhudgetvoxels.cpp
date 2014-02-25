#include "textfieldhudgetvoxels.h"

#include <vector>

#include "ui/voxelfont.h"
#include "ui/letter.h"
#include "textfieldhudget.h"
#include "hud.h"
#include "voxel/voxelrenderer.h"

TextFieldHudgetVoxels::TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget) :
m_textFieldHudget(textFieldHudget),
m_voxelFont(new VoxelFont()) {

}

void TextFieldHudgetVoxels::setContent(std::string content) {
    m_content = content;
}

void TextFieldHudgetVoxels::draw() {
    std::vector<Letter*> letters;
    //m_voxelFont->drawString("test",glm::vec3(0,0,1),FontSize::s3x5);
    m_voxelFont->drawString(m_content, m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)), m_textFieldHudget->worldOrientation(glm::vec3(0, 0, 1)), FontSize::s5x7, 0.04f);
    /*for (Letter* letter : letters) {
        letter->transform().setOrientation(m_textFieldHudget->worldOrientation(glm::normalize(-letter->transform().position())));
        letter->transform().setPosition(m_textFieldHudget->worldPosition(glm::normalize(letter->transform().position())));
        VoxelRenderer::instance()->draw(*letter);
    }*/
}