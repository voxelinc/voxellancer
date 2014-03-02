#include "textfieldhudgetvoxels.h"

#include <vector>

#include "ui/voxelfont.h"
#include "ui/letter.h"
#include "textfieldhudget.h"
#include "hud.h"
#include "voxel/voxelrenderer.h"

#include <glm/gtx/intersect.hpp>

#include "utils/geometryhelper.h"

TextFieldHudgetVoxels::TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget) :
m_textFieldHudget(textFieldHudget),
m_voxelFont(new VoxelFont()) 
{

}

TextFieldHudgetVoxels::TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, std::string content, glm::vec3 direction, float scale) :
m_textFieldHudget(textFieldHudget),
m_voxelFont(new VoxelFont()),
m_content(content),
m_direction(direction),
m_scale(scale)
{
    m_width = 7 * m_scale;
    m_height = 5 * m_scale;
    m_offset = -1.f * ((m_content.length() - 1) / 2.0f) * m_width;
}

void TextFieldHudgetVoxels::setContent(std::string content) {
    m_content = content;
    m_offset = -1.f * ((m_content.length() - 1) / 2.0f) * m_width;
}

void TextFieldHudgetVoxels::draw() {
    std::vector<Letter*> letters;
    m_voxelFont->drawString(m_content, m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)), m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)), FontSize::s5x7, 0.04f, FontAlign::aCenter);
}

const glm::vec3 TextFieldHudgetVoxels::upperLeft() const {
    return m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) * glm::vec3(m_offset + m_width * 0 - m_width / 2, m_height, 0);
}

const glm::vec3 TextFieldHudgetVoxels::lowerLeft() const {
    return m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) * glm::vec3(m_offset + m_width * 0 - m_width / 2, -m_height, 0);
}
const glm::vec3 TextFieldHudgetVoxels::upperRight() const {
    return m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) * glm::vec3(m_offset + m_width * m_content.length() - m_width / 2, m_height, 0);
}
const glm::vec3 TextFieldHudgetVoxels::lowerRight() const {
    return m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) * glm::vec3(m_offset + m_width * m_content.length() - m_width / 2, -m_height, 0);
}

bool TextFieldHudgetVoxels::isAt(const Ray& ray) const {
    return GeometryHelper::intersectRectangle(&ray, upperLeft(), lowerLeft(), lowerRight(), upperRight());
}

float TextFieldHudgetVoxels::width() {
    return m_width;
}

float TextFieldHudgetVoxels::height() {
    return m_height;
}

float TextFieldHudgetVoxels::scale() {
    return m_scale;
}