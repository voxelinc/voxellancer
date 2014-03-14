#pragma once

#include <memory>
#include <string>

#include "hudget.h"
#include "ui/voxelfontconstant.h"

class TextFieldHudget;
class VoxelFont;

class TextFieldHudgetVoxels{
public:
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, glm::vec3 direction, float scale = 0.5f, std::string content = "", FontSize fontSize = FontSize::SIZE5x7);

    void setContent(std::string content);

    void update(float deltaSec);
    void draw();

    virtual bool isAt(const Ray& ray) const;
    const glm::vec3 upperLeft() const;
    const glm::vec3 lowerLeft() const;
    const glm::vec3 upperRight() const;
    const glm::vec3 lowerRight() const;

    float width();
    float height();
    float scale();


protected:
    FontSize m_fontSize;
    TextFieldHudget* m_textFieldHudget;
    std::string m_content;
    VoxelFont* m_voxelFont;
    glm::vec3 m_direction;
    float m_width, m_height, m_scale;
    float m_offset;
    glm::vec3 offsetToCenter(bool left, bool upper);
};

