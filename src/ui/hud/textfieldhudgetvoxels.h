#pragma once

#include <memory>
#include <string>

#include "hudget.h"

class VoxelFont;
class TextFieldHudget;

class TextFieldHudgetVoxels{
public:
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget);
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, std::string content, glm::vec3 direction, float scale);

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
    TextFieldHudget* m_textFieldHudget;
    std::string m_content;
    VoxelFont* m_voxelFont;
    glm::vec3 m_direction;
    float m_width, m_height, m_scale;
    float m_offset;
};

