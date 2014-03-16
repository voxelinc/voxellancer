#pragma once

#include <memory>
#include <string>

#include "hudget.h"
#include "ui/voxelfontconstants.h"

class TextFieldHudget;
class VoxelFont;

class TextFieldHudgetVoxels{
public:
    TextFieldHudgetVoxels(TextFieldHudget* textFieldHudget, glm::vec3 direction, float scale = 0.5f, std::string content = "", FontSize fontSize = FontSize::SIZE5x7);

    virtual void setContent(std::string content);

    //virtual void update(float deltaSec);
    virtual void draw();

    virtual bool isAt(const Ray& ray) const;

    float width();
    float height();
    float scale();

protected:
    const glm::vec3 upperLeft() const;
    const glm::vec3 lowerLeft() const;
    const glm::vec3 upperRight() const;
    const glm::vec3 lowerRight() const;

    TextFieldHudget* m_hudget;
    glm::vec3 worldPosition()  const;
    glm::quat worldOrientation() const;

    FontSize m_fontSize;
    std::string m_content;
    VoxelFont* m_voxelFont;
    glm::vec3 m_direction;
    float m_width, m_height, m_scale;
    float m_offset;
    const glm::vec3 offsetToCenter(bool upper, bool left) const;
};

