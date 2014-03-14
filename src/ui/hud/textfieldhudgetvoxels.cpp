#include "textfieldhudgetvoxels.h"

#include <vector>

#include "ui/voxelfont.h"
#include "ui/letter.h"
#include "textfieldhudget.h"
#include "hud.h"
#include "voxel/voxelrenderer.h"

#include <glm/gtx/intersect.hpp>

#include "utils/geometryhelper.h"

TextFieldHudgetVoxels::TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, glm::vec3 direction, float scale, std::string content, FontSize fontSize) :
m_textFieldHudget(textFieldHudget),
m_voxelFont(VoxelFont::instance()),
m_content(content),
m_direction(direction),
m_scale(scale),
m_fontSize(fontSize)
{
    m_width = m_voxelFont->letterWidth(fontSize) * m_scale;
    m_height = m_voxelFont->letterWidth(fontSize) * m_scale;
    m_offset = -1.f * ((m_content.length() - 1) / 2.0f) * m_width;
}

void TextFieldHudgetVoxels::setContent(std::string content) {
    m_content = content;
    m_offset = -1.f * ((m_content.length() - 1) / 2.0f) * m_width;
}

void TextFieldHudgetVoxels::draw() {
    m_voxelFont->drawString(m_content, m_textFieldHudget->worldPosition(m_direction), m_textFieldHudget->worldOrientation(m_direction), m_fontSize, m_scale, FontAlign::CENTER);
}

const glm::vec3 TextFieldHudgetVoxels::upperLeft() const {
    return m_textFieldHudget->worldPosition(m_direction) + m_textFieldHudget->worldOrientation(m_direction) * glm::vec3(m_offset + m_width * 0 - m_width / 2, m_height, 0);
}

const glm::vec3 TextFieldHudgetVoxels::lowerLeft() const {
    return m_textFieldHudget->worldPosition(m_direction) + m_textFieldHudget->worldOrientation(m_direction) * glm::vec3(m_offset + m_width * 0 - m_width / 2, -m_height, 0);
}
const glm::vec3 TextFieldHudgetVoxels::upperRight() const {
    return m_textFieldHudget->worldPosition(m_direction) + m_textFieldHudget->worldOrientation(m_direction) * glm::vec3(m_offset + m_width * m_content.length() - m_width / 2, m_height, 0);
}
const glm::vec3 TextFieldHudgetVoxels::lowerRight() const {
    return m_textFieldHudget->worldPosition(m_direction) + m_textFieldHudget->worldOrientation(m_direction) * glm::vec3(m_offset + m_width * m_content.length() - m_width / 2, -m_height, 0);
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

glm::vec3 TextFieldHudgetVoxels::offsetToCenter(bool left, bool upper) {
    float horizontalOffset, verticalOffset;
    if (left) {
        horizontalOffset = (float)m_content.length();
    } else {
        horizontalOffset = 0;
    }
    if (upper) {
        verticalOffset = m_height;
    } else {
        verticalOffset = -m_height;
    }

    return glm::vec3(m_offset + m_width*horizontalOffset - m_width / 2, verticalOffset, 0);
}