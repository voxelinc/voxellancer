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

TextFieldHudgetVoxels::TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, std::string content) :
m_textFieldHudget(textFieldHudget),
m_voxelFont(new VoxelFont()),
m_content(content)
{

}

void TextFieldHudgetVoxels::setContent(std::string content) {
    m_content = content;
}

void TextFieldHudgetVoxels::draw() {
    std::vector<Letter*> letters;
    m_voxelFont->drawString(m_content, m_textFieldHudget->worldPosition(glm::vec3(0, 0, -1)), m_textFieldHudget->worldOrientation(glm::vec3(0, 0, -1)), FontSize::s5x7, 0.04f, FontAlign::aCenter);
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
    //isAt = isAt || glm::intersectRayTriangle<glm::vec3>(ray.origin(), ray.direction(), lowerRight, lowerLeft, upperLeft, intersectionPoint);
    //isAt = isAt || glm::intersectRayTriangle<glm::vec3>(ray.origin(), ray.direction(), upperRight, lowerRight, upperLeft, intersectionPoint);
    isAt = isAt || glm::intersectRayTriangle<glm::vec3>(ray.origin(), ray.direction(), upperRight, upperLeft, lowerRight, intersectionPoint);
    isAt = isAt || glm::intersectRayTriangle<glm::vec3>(ray.origin(), ray.direction(), lowerRight, upperLeft, lowerLeft, intersectionPoint);
    if (isAt) {
        printf("hit\n");
    } else {
        printf("no hit\n");
    }
    return isAt;
}