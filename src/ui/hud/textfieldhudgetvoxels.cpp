#include "textfieldhudgetvoxels.h"

#include <vector>

#include "ui/voxelfont.h"

TextFieldHudgetVoxels::TextFieldHudgetVoxels() :
m_voxelFont() {

}

void TextFieldHudgetVoxels::setContent(std::string content) {
    m_content = content;
}

void TextFieldHudgetVoxels::draw() {
    std::vector<Letter*>* letters = new std::vector<Letter*>;
    m_voxelFont->getLetters(m_content, FontSize::s5x7, letters);
}