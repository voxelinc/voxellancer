#include "textfieldhudgetvoxels.h"

#include <vector>

#include "ui/voxelfont.h"
#include "ui/letter.h"
#include "textfieldhudget.h"
#include "hud.h"
#include "voxel/voxelrenderer.h"

#include <glm/gtx/intersect.hpp>

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

glm::vec3 TextFieldHudgetVoxels::upperLeft() {
    return glm::vec3(m_offset + m_width * 0 - m_width / 2, m_height, 0);
}

glm::vec3 TextFieldHudgetVoxels::lowerLeft() {
    return glm::vec3(m_offset + m_width * 0 - m_width / 2, -m_height, 0);
}
glm::vec3 TextFieldHudgetVoxels::upperRight() {
    return glm::vec3(m_offset + m_width * m_content.length() - m_width / 2, m_height, 0);
}
glm::vec3 TextFieldHudgetVoxels::lowerRight() {
    return glm::vec3(m_offset + m_width * m_content.length() - m_width / 2, -m_height, 0);
}

bool TextFieldHudgetVoxels::isAt(const Ray& ray) const {
    glm::vec3 upperLeft, lowerLeft, upperRight, lowerRight;
    float width = 7 * 0.04f;
    float height = 5 * 0.04f;
    float intoffset = -1.f * ((m_content.length() - 1) / 2.0f) * width;
    lowerLeft = m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) *glm::vec3(intoffset + width * 0 - width/2, -height, 0);
    upperLeft = m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) *glm::vec3(intoffset + width * 0 - width / 2, height, 0);
    lowerRight = m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) *glm::vec3(intoffset + width * m_content.length() - width / 2, -height, 0);
    upperRight = m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)) + m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)) *glm::vec3(intoffset + width * m_content.length() - width / 2, height, 0);
    glm::vec3 intersectionPoint;
    bool isAt = false;
    isAt = isAt || glm::intersectRayTriangle<glm::vec3>(ray.origin(), ray.direction(), upperRight, upperLeft, lowerRight, intersectionPoint);
    isAt = isAt || glm::intersectRayTriangle<glm::vec3>(ray.origin(), ray.direction(), lowerRight, upperLeft, lowerLeft, intersectionPoint);
    if (isAt) {
        printf("hit\n");
    } else {
        printf("no hit\n");
    }
    return isAt;
}